!
function(r) {
	if (r) {
		var t = {
			redefineGetter: function(e, r, t) {
				var i = function() {
					return t
				};
				e.__defineGetter__ ? e.__defineGetter__(r, i) : Object.defineProperty && Object.defineProperty(e, r, {
					get: i
				})
			},
			disableShowDialog: function() {
				for (var e = function() {
					return ! 0
				},
				r = ["alert", "prompt", "confirm", "showModalDialog", "showModelessDialog"], t = 0; t < r.length; ++t) this.redefineGetter(window, r[t], e)
			},
			overrideProperties: function(e) {
				if (e && e.length) for (var r = 0; r < e.length; ++r) {
					var t = e[r];
					t && t.instance && t.property && this.redefineGetter(t.instance, t.property, t.value)
				}
			},
			getOverrideProperty: function(e, r, t, i) {
				if (!e || !t || !i) return null;
				if ("object" == typeof r && "object" == typeof e && !r.hasOwnProperty(t)) {
					var n = e[t];
					if ("function" == typeof n) {
						var o = e[t];
						n = function() {
							return o.apply(e)
						}
					}
					Object.defineProperty(r, t, {
						value: n,
						writable: !1
					})
				}
				return {
					instance: e,
					property: t,
					value: i
				}
			},
			isAndroid: function(e) {
				return !! e.userAgent.match(/android/g)
			},
			overrideAndroidSpecal: function(e, r) {
				if (this.isAndroid(e)) {
					var t = [];
					t.push(this.getOverrideProperty(navigator, r, "getBattery", !0)),
					t.push(this.getOverrideProperty(navigator, r, "vibrate", !0)),
					t.push(this.getOverrideProperty(navigator, r, "hardwareConcurrency", 4)),
					this.overrideProperties(t)
				}
			},
			overridePropertiesByDev: function(r) {
				var t = window._ftk_window || {};
				window._ftk_window = t;
				var i = [];
				t.navigator = t.navigator || {},
				t.navigator.connection = t.navigator || {},
				i.push(this.getOverrideProperty(navigator, t.navigator, "platform", r.navigator && r.navigator.platform || r.platform)),
				i.push(this.getOverrideProperty(navigator, t.navigator, "userAgent", r.userAgent)),
				i.push(this.getOverrideProperty(navigator, t.navigator, "plugins", {
					length: 0
				}));
				var n = !(!r.navigator || !r.navigator.javaEnabled) || !!r.javaEnabled;
				if (i.push(this.getOverrideProperty(navigator, t.navigator, "javaEnabled", (function() {
					return n
				}))), i.push(this.getOverrideProperty(navigator, t.navigator, "characterSet", void 0)), i.push(this.getOverrideProperty(navigator, t.navigator, "browserLanguage", void 0)), i.push(this.getOverrideProperty(navigator, t.navigator, "language", r.navigator && r.navigator.language || r.language)), i.push(this.getOverrideProperty(navigator.connection, t.navigator.connection, "effectiveType", r.navigator && r.navigator.effectiveType)), "screen" in r && (t.screen = t.screen || {},
				i.push(this.getOverrideProperty(screen, t.screen, "width", r.screen.width)), i.push(this.getOverrideProperty(screen, t.screen, "height", r.screen.height)), i.push(this.getOverrideProperty(screen, t.screen, "availWidth", r.screen.availableWidth || r.screen.width)), i.push(this.getOverrideProperty(screen, t.screen, "availHeight", r.screen.availableHeight || r.screen.height)), i.push(this.getOverrideProperty(screen, t.screen, "colorDepth", r.screen.colorDepth || 32)), i.push(this.getOverrideProperty(screen, t.screen, "pixelDepth", r.screen.pixelDepth || 32))), ("window" in r || "screen" in r) && (i.push(this.getOverrideProperty(window, t, "innerWidth", r.window && r.window.innerWidth || r.screen && r.screen.width)), i.push(this.getOverrideProperty(window, t, "innerHeight", r.window && r.window.innerHeight || r.screen && r.screen.height)), i.push(this.getOverrideProperty(window, t, "outerWidth", r.window && r.window.outerWidth || r.screen && r.screen.width)), i.push(this.getOverrideProperty(window, t, "outerHeight", r.window && r.window.outerHeight || r.screen && r.screen.height)), i.push(this.getOverrideProperty(window, t, "devicePixelRatio", r.window && r.window.devicePixelRatio))), "object" == typeof r.document && (t.document = t.document || {},
				i.push(this.getOverrideProperty(document, t.document, "characterSet", r.document.characterSet))), "render" in r && !WebGLRenderingContext.prototype.hookRender) {
					WebGLRenderingContext.prototype.hookRender = !0;
					var o = WebGLRenderingContext.prototype.getParameter;
					WebGLRenderingContext.prototype.getParameter = function(r) {
						return 37446 == r ? e.render: o.apply(this, [r])
					}
				}
				this.overrideProperties(i),
				this.isAndroid(r) && this.overrideAndroidSpecal(r, t.navigator)
			},
			mute: function() {
				var e = this,
				r = function() {
					e.muteByTag("video"),
					e.muteByTag("audio")
				};
				r(),
				setInterval(r, 5e3)
			},
			muteByTag: function(e) {
				var r = document.getElementsByTagName(e);
				if (r && !(r.length <= 0)) for (var t = 0; t < r.length; ++t) {
					var i = r[t];
					i.__lookupSetter__ && (i.__lookupSetter__("muted") && (i.muted = !0), i.__lookupSetter__("volume") && (i.volume = 0))
				}
			},
			inject: function(e) {
				window.__tv_fun_toolkits_dolphin_already_injection_ || (window.__tv_fun_toolkits_dolphin_already_injection_ = !0, this.disableShowDialog(), this.overridePropertiesByDev(e), this.mute())
			}
		};
		t.inject(r)
	}
} ({
	"userAgent": "Mozilla/5.0 (Linux; Android 4.4.4; vivo Y27 Build/KTU84P) AppleWebKit/537.36 (KHTML, like Gecko) Version/4.0 Chrome/33.0.0.0 Mobile Safari/537.36 lite baiduboxapp/4.1.0.11 (Baidu; P1 4.4.4)",
	"javaEnabled": false,
	"platform": "Linux armv8l",
	"screen": {
		"width": 720,
		"height": 1280
	}
});