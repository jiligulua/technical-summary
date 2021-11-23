(function (dev) {
    if (!dev) {
        return
    }

    var impl = {
        redefineGetter: function (inst, property, v) {
            var funcimpl = function () {
                return v
            };

            if (inst.__defineGetter__) {
                inst.__defineGetter__(property, funcimpl);
            }
            else if (Object.defineProperty) {
                Object.defineProperty(inst, property, {get: funcimpl});
            }
        },

        disableShowDialog: function () {
            //禁用函数实现
            var disableFunc = function () {
                return true
            };

            var windowDisableProperty = ['alert', 'prompt', 'confirm', 'showModalDialog', 'showModelessDialog'];
            for (var i = 0; i < windowDisableProperty.length; ++i) {
                this.redefineGetter(window, windowDisableProperty[i], disableFunc)
            }
        },
        
        overrideProperties: function (properties) {
            if (!properties || !properties.length) {
                return
            }

            for (var i = 0; i < properties.length; ++i) {
                var p = properties[i];
                if (!p ||!p.instance || !p.property) {
                    continue;
                }

                this.redefineGetter(p.instance, p.property, p.value)
            }
        },

        getOverridePropertyDescription: function(inst, backInst, property, value) {
            if (!inst || !property) {
                return null
            }

            if (typeof backInst == 'object' && typeof inst == 'object') {
                if (!backInst.hasOwnProperty(property)) {
                    var v = inst[property]
                    if (typeof v == 'function') {
                        var func = inst[property]
                        v = function() {
                            return func.apply(inst)
                        }
                    }

                    Object.defineProperty(backInst, property, {
                        value: v,
                        writable: false
                    })
                }
            }

            return {
                instance: inst,
                property: property,
                value: value
            }
        },
        
        isAndroid: function (dev) {
            var ua = dev.userAgent
            return !!ua.match(/android/g)
        },
        
        overrideAndroidSpecal: function (dev, backInst) {
            if (!this.isAndroid(dev)) {
                return
            }

            var properties = [];
            properties.push(this.getOverridePropertyDescription(navigator, backInst, 'getBattery', true));
            properties.push(this.getOverridePropertyDescription(navigator, backInst, 'vibrate', true));
            properties.push(this.getOverridePropertyDescription(navigator, backInst, 'hardwareConcurrency', 4));

            this.overrideProperties(properties)
        },

        overridePropertiesByDev: function (dev) {
            var _ftk_window = window._ftk_window || {}
            window._ftk_window = _ftk_window

            var properties = [];
            _ftk_window.navigator = _ftk_window.navigator || {}
            properties.push(this.getOverridePropertyDescription(navigator, _ftk_window.navigator, 'platform', dev.platform));
            properties.push(this.getOverridePropertyDescription(navigator, _ftk_window.navigator, 'userAgent', dev.userAgent));
            properties.push(this.getOverridePropertyDescription(navigator, _ftk_window.navigator, 'plugins', {length: 0}));

            var javaEnabled = false
            if ('javaEnabled' in dev) {
                javaEnabled = !!dev.javaEnabled
            }
            properties.push(this.getOverridePropertyDescription(navigator, _ftk_window.navigator, 'javaEnabled', function () {
                return javaEnabled
            }));

            properties.push(this.getOverridePropertyDescription(navigator, _ftk_window.navigator, 'characterSet', undefined));
            properties.push(this.getOverridePropertyDescription(navigator, _ftk_window.navigator, 'browserLanguage', undefined));

            if ('language' in dev) {
                properties.push(this.getOverridePropertyDescription(navigator, _ftk_window.navigator, 'language', dev.language))
            }

            if ('screen' in dev) {
                _ftk_window.screen = _ftk_window.screen || {}
                properties.push(this.getOverridePropertyDescription(screen, _ftk_window.screen, 'width', dev.screen.width))
                properties.push(this.getOverridePropertyDescription(screen, _ftk_window.screen, 'height', dev.screen.height))
                properties.push(this.getOverridePropertyDescription(screen, _ftk_window.screen, 'colorDepth', dev.screen.colorDepth || 32))
                properties.push(this.getOverridePropertyDescription(screen, _ftk_window.screen, 'pixelDepth', dev.screen.pixelDepth || 32))

                properties.push(this.getOverridePropertyDescription(screen, _ftk_window.screen, 'availWidth', dev.screen.availWidth || dev.screen.width))
                properties.push(this.getOverridePropertyDescription(screen, _ftk_window.screen, 'availHeight', dev.screen.availHeight || dev.screen.height))
            }

            if ('window' in dev || 'screen' in dev) {
                properties.push(this.getOverridePropertyDescription(window,
                     _ftk_window, 
                    'innerWidth', 
                    (dev.window && dev.window.innerWidth) || dev.screen.width))
                properties.push(this.getOverridePropertyDescription(window, 
                    _ftk_window, 
                    'innerHeight', 
                    (dev.window && dev.window.innerHeight) || dev.screen.height))

                properties.push(this.getOverridePropertyDescription(window, 
                    _ftk_window, 
                    'outerWidth', 
                    (dev.window && dev.window.outerWith) || dev.screen.width))
                properties.push(this.getOverridePropertyDescription(window,
                     _ftk_window, 
                    'outerHeight', 
                    (dev.window && dev.window.outerHeight) || dev.screen.height))

                if (dev.window && 'devicePixelRatio' in dev.window) {
                    properties.push(this.getOverridePropertyDescription(window, 
                        _ftk_window, 
                        'devicePixelRatio', 
                        dev.window.devicePixelRatio))
                }
            }

            if (typeof dev.document == 'object') {
                _ftk_window.document = _ftk_window.document || {}
                properties.push(this.getOverridePropertyDescription(document, 
                    _ftk_window.document, 
                    'characterSet', 
                    dev.document.characterSet))
            }

            this.overrideProperties(properties)

            if (this.isAndroid(dev)) {
                this.overrideAndroidSpecal(dev,  _ftk_window.navigator)
            }
        },
        
        mute: function () {
            var obj = this;
            var muteimpl = function () {
                obj.muteByTag('video');
                obj.muteByTag('audio');
            };

            muteimpl();
            setInterval(muteimpl, 5000);
        },
        
        muteByTag: function (tag) {
            var eles = document.getElementsByTagName(tag)
            if (!eles || eles.length <= 0) {
                return
            }

            for (var i = 0; i < eles.length; ++i) {
                var e = eles[i];
                if (!e.__lookupSetter__) {
                    continue
                }

                if (e.__lookupSetter__('muted')) {
                    e.muted = true;
                }
                if (e.__lookupSetter__('volume')) {
                    e.volume = 0;
                }
            }
        },

        inject: function (dev) {
            if (window.__tv_fun_toolkits_dolphin_already_injection_) {
                return
            }
            window.__tv_fun_toolkits_dolphin_already_injection_ = true;

            this.disableShowDialog();
            this.overridePropertiesByDev(dev);
            this.mute();
        }
    };

    impl.inject(dev);
//})(__tv_fun_toolkits_dolphin_injection_param__);
})(
	{
		"userAgent": "Mozilla/5.0 (Linux; Android 4.4.4; vivo Y27 Build/KTU84P) AppleWebKit/537.36 (KHTML, like Gecko) Version/4.0 Chrome/33.0.0.0 Mobile Safari/537.36 lite baiduboxapp/4.1.0.11 (Baidu; P1 4.4.4)",
		"javaEnabled": false,
		"platform": "Linux armv8l",
		"screen": {
			"width": 720,
			"height": 1280
	}
}
);