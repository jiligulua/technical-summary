# 1.MXNet框架入门
1. 有关MXNet
2. 从一个五脏俱全的例子说起
3. MXNet核心接口分析
4. 面向实战的例子
5. 模型部署

# 2.关于MXNet
1. MXNet是由DMLC开源的深度学习开发包，由于可以使用命令与符号式两种变成风格，一次MXNet的名称也叫做mixed-net。现在已经成为Apache的孵化项目。

是DMLC多年集成的结晶。

2. 优势-Why MXNet？

一个深度学习框架需要哪些？ 首先需要容易去定义模型，然后需要快速训练模型，最后能够把训练好的模型能够在实践应用中部署，而MXNex在这三个方面表现的突出。

-	接口足够清晰，简单，易于用户Hack（容易定制）
-	显存利用与多卡并行效率极高
-	成熟的PC，移动端部署方案，依赖少。所以说非常方便部署训练好的模型
-	支持Python，R，Matlab，JavaScript等众多不同语言
-	具有静态图编程接口

3. 思考

要完成一个完整的训练需要哪些功能模块？

	1. 读取数据
	2. 定义网络结构
	3. 优化器，怎么去优化网络中的参数，比如说梯度下降，还有带动量的梯度下降
	4. 定义学习率衰减方式，最后在训练过程中改变我们的学习率
	5. 衡量模型好坏，性能，速度等，在训练过程中不停的监控模型训练的好坏，性能还有速度
	6. 执行网络，从网络获取节点值，在测试过程中获取某个网络节点的值		 
	7. 其它能监控网络执行过程的模块

	所以说，需要这些基本的功能模块

4. MXNet一个基本的例子

看它都拥有什么基本的功能模块，如下使用了mixed-net，对0到9的10个数字进行了分类。

	import mxnet as mx

	mnist = mx.test_utils.get_mnist()
	batch_size = 100

	// DataIter使用NDArrayIter数组迭代器，输入数组数据，得到它的迭代器
	train_iter = mx.io.NDArrayIter(mnist['train_data'], mnist['train_label'], batch_size,shuffle=true) 
	val_iter = mx.io.NDArryIter(mnist['test_data'], mnist['test_label'], batch_size)
	
	// 使用Symbol构成的网络
	data = mx.sym.var('data')
	data = mx.sym.flatten(data=data)
	fcl = mx.sym.FullyConnected(data=data, num_hidden=128)
	actl = mx.sym.Activation(data=fc1, act_type='relu')
	fc2 = mx.sym.FullyConnected(data=act1, num_hidden=10
	mlp = mx.sym.SoftmaxOutput(data=fc2, name='softmax')

	// 定义了Module（模块）和context，这个模块把其它的不同的接口封装在一起，完成整个训练过程，是一个比较高级的接口
	mlp_model = mx.mod.Module(symbol=mlp, context=mx.cpu())

	// 学习衰减策略，每80步，衰减为前面的90%，即之前的0.9倍， LR Scheduler 
	lr_decay = mx.lr_scheduler.FactorScheduler(step=88, factor= .9)
	
	// 优化器Optimizer 
	optimizer = mx.optimizer.SGD(
					learning_rat = 0.01, // 基础学习率是0.01
					wd = 0.0005,
					momentum = 0.9, // 带momentum的优化器，带0.9
					lr_scheduler = lr_decay)

	// 定义个Metric，比如说在循良过程中衡量它的精度是多少，以便于我们知道目前处于一个怎么样的情况
	metric = mx.metric.Accuracy()	 

	// 定义了两个callback，在训练过程中方便MXNet去回调，完成你想要的某些功能
	speed_callback = mx.callback.Seedometer(batch_size, 20)  // 检测模型的训练速度
	save_checkpoint = mx.callback.do_checkpoint('/tmp/model', 1) // 模型一个epoch结束之后，去保存我们的模型

	// kvstore，可以简单理解为参数服务器，local是说我们把参数服务器放在内存中
	kvstore = mx.kv.create('local')

	mlp_modle.fit(train_iter,
				  eval_data = vall_iter,
				  optimizer = optimizer,
				  eval_metric = metric,
				  batch_end_callback = speed_callback,
				  epoch_end_callback = save_checkpoint,
				  num_epoch = 10,
				  kvstore=kvstore)

这个版本是精简版，为了篇幅的原因。那么使用了哪些功能模块。



# 2.MXNet核心接口分析

主要包含这11个接口

1. Context：指定我们运行的设备，模型是在CPU还是GPU上运行
2. NDArray：Python与C++交互的数据对象，MXNet呈现给用户的数据都是以NDArray的形式
3. DataIter：数据迭代器，为训练提供batch数据
4. Symbol：用来定义网络
5. LR Scheduler：定义学习率衰减策略，在训练过程中改变我们的学习率
6. Optimizer：优化器，决定如何更新权值参数
7. Executor：进行图的前向计算与反向梯度推导，但是它不负责更新参数，更新参数是由Optimizer来完成的
8. Metric：查看模型训练过程指标，比如说精度（Accuracy）
9. Callback：MXNet在训练过程中不间断的回调我定义的函数，用来完成我想要的一些功能
10. KVStore：跨设备的键值存储，相对来说是一个参数服务器，用来维护不同设备之间共有的参数，去同步和更新
11. Module：该对象把前面10模块封装在一个模块里面，使它们之间协作去完成一次完整的训练过程和测试

接下来逐个讲解接口，以及它们之间的协作

## 2.1 Context
用于指定运行设备的接口
定义方式：
1. CPU Context： 通过mxnex.cpu(0)定义，这里的设备id为0，会默认使用所有CPU核心
2. GPU Context： 通过mxnex.gpu(0)定义，这里的设备id，决定使用哪块GPU设备。如果需要使用多卡的并行训练，比如说需要多块gpu并行使用的话，可以定义多个Context，并用list把它们放在一起，如[mx.gpu(0), mx.gpu(1)]
3. 使用要求整个代码中的context，须保持一致，且如果使用gpu，则要使用的GPU id保持一致

对比MXNet与TensorFlow：
1. tf.device("/gpu:1") == mx.gpu(device_id=1)
2. tf.device("/cpu:0") == mx.cpu(device_id=0)

## 2.2 MXNex核心接口-NDArray

NDArray：用于命令式编程的接口
简单理解：一个同时支持CPU与GPU的NumPy，两者可轻松进行转换。NumPy只是CPU的一个进行矩阵运算的开发包，就是一个工具

- 简单初始化方式
	
	import numpy as np
	from mxnet import nd

	np_array = np.arange(10, dtype=np.float32).reshape((2,5))
	mx_array = nd.arange(10, dtype=np.float32).reshape((2,5))

	print('np_array:\n', np_array)
	print('mx_array:\n', mx_array)

numpy和NDArray(nd)它们的定义方式一样，仅仅是包名的不同，后面的函数几乎是一致的。也就是说NDArray和NumPy的接口基本是一致的。唯一不同的是NDArray涉及到不同设备之间的矩阵运算和赋值

NDArray：用于命令式编程的接口

- 线性代数的例子，完成内积的运算

	print('np_array inner product:\n', np_array.dot(np_array.T))
	print('mx_array inner product:\n', nd_array.dot(mx_array, mx_array.T))

- NDArray和NumPy数组的相互转换

	# from numpy array to mxnet ndarry
	np_ones = np.ones(shape=(2,2))
	from_np_aray = nd.array(np_ones, dtype=np.float32)
	print(from_np_array)

	# from mxnet array to numpy ndarray
	mx_ones = nd.ones(shape=(2,2), dtype=np.float32)
	from_mx_array = mx_ones.asnumpy()
	print(from_mx_array)

- MXNex NDArray在CPU与GPU上的执行

	import mxnext as mx
	# init mxnet ndarray on cpu
	mx_cpu = nd.ones(shape=(2,2), ctx=mx.cpu(0))
	# init mxnet ndarray on gpu
	mx_gpu = nd.ones(shape=(2,2), ctx=mx.gpu(0))
	print(mx_cpu + mx_gpu)
	
	会报错，因为是在不同的设备上，不能简单的进行想加

- Host与Device上的NDArray的复制与移动操作	

从内存到GPU的显存上的NDArray的复制和移动操作
	
	1. 不同设备之间移动数据

	# init mxnet ndarray on cpu
	mx_cpu = nd.ones(shape=(2,2), ctx=mx.cpu(0))
	print('mx cpu context: ', mx_cpu.context)
	host_to_gpu = mx_cpu.as_in_context(mx.gpu(0)) // 进行了gpu的切换
	print('host_to_gpu context: ', host_to_gpu.context)


	# init mxnet ndarray on cpu
	mx_cpu = nd.ones(shape=(2,2), ctx=mx.cpu(0))
	# init mxnet ndarray on gpu
	mx_gpu = nd.ones(shape=(2,2), ctx=mx.gpu(0))
	print(mx_cpu.as_in_context(mx.gpu(0)) + mx_gpu) // 这样在相同的设备上，就可以相加了


	2.不同设备之间复制数据
	mx_gpu_0 = nd.ones(shape=(2,2), ctx=mx.gpu(0))
	mx_gpu_1 = nd.zeros(shape=(2,2), ctx=mx.gpu(1))
	print("before copy: \n", mx_gpu_1)
	mx_gpu_0.copyto(mx_gpu_1)
	print("after copy: \n", mx_gpu_1)


- 总结，为什么MXNet需要NDArray这样的对象呢？

-	NDArray之于MXNet相当于NumPy之于TensorFlow
-	MXNet执行网络，输入的数据，与获取节点数据对象都都是NDArray，是客户端与底层C++交互的数据接口
-	MXNet使用Python定义Op，其中使用的面向过程的计算，都是基于NDArray
-	MXNet新出的实现动态网络的Gluon API，大量使用了NDArray提供的操作。


## 2.3 DataIter数据迭代器

mx.io.DataIter用于提供输入数据的接口

- 初步认识

	mnist = mx.test_utils.get_mnist()
	batch_size = 1
	print("data shape {} and data type {}".format(mnist['train_data'].shape, type(mnist['train_data'])))
	train_iter = mx.io.NDArrayIter(mnist['train_data'], mnist['train_label'], batch_size, shuffle=True)
	batch = train_iter.next()
	print(type(batch))
	print('data shape {} and data type {}'.format(batch.data[0].shape, type(batch.data[0])))
	print('label shape {} and label type {}'.format(batch.label[0].shape, type(batch.label[0])))


	60000张图片，单通道，28*28，0到9，由10个分类
	data shape (60000, 1, 28, 28) and data type <class 'numpy.ndarray'>
	<class 'mxnet.io.DataBatch'> mxnet中输入网络的是DataBatch对象
	data shape (1, 1, 28, 28) and data type <class 'mxnet.ndarray.ndarray.NDArray'>
	label shape (1,) and label type <class 'mxnet.ndarray.ndarray.NDArray'>

- 工作原理

数据迭代器一个Epoch结束后，会抛出StopIteration异常


	mnist = mx.test_utils.get_mnist() // 由60000个数据*1*28*28，batch（一批量）为1，就是迭代60000次，
	batch_size = 1
	print("data shape {} and data type {}".format(mnist['train_data'].shape, type(mnist['train_data'])))
	train_iter = mx.io.NDArrayIter(mnist['train_data'], mnist['train_label'], batch_size, shuffle=True)
	count = 0
	while True:
		try:
			train_iter.next()
			count += 1
			if count % 1000 == 0 : print('Current Batch Num: ', count)
		except StopIteration:
			print('Read to End')
			break;

	StopIteration用于Epoch的计算，如
		except StopIteration：
			train_iter.reset()  // 使数据集又指向开头，就像C++中迭代器的begin()
			epoch += 1
			print('Epoch Num: ', epoch)
			if epoch >= 10: break;


- 自定义一个DataIter

自定义一个数据迭代器

	class DemoDataIter(mx.io.DataIter):
		def __init__(self, batch_size, mnist):
			super(DemoDataIter, self).__init__(batch_size)
			self.idx = 0
			self.sample_size = 60000
			self.batch_size = batch_size
			self.minist_data = mnist['train_data']
			self.minist_label = mnist['train_label']
			self.provide_data = [('data', (batch_size, 1, 28, 28))]
			self.provide_label = [('label', (batch_size, ))]

		def next(self):
			if self.idx + self.batch.size > self.sample_size:
				raise StopIteration
			data = self.mnist_data[self.idx: self.idx + self.batch_size]
			label = self.mnist_label[self.idx: self.idx + self.batch_size]
			data_batch = mx.io.DataBatch(data=[data], label=[label])
			self.idx += self.batch_size
			return data_batch

		def reset(self):
			self.idx = 0


		mnist = mx.text_utils.get_mnist()
		iter = DemoDataIter(2, minist)
		epoch = 0
		while True:
			try:
				iter.next()
			except StopIteration:
				iter.reset()
				epoch += 1 // 数据完成之后才计数，计数满足用户设置的epoches之后，整个训练过程就会停止
				print('Epoch Num: ', epoch)
				if epoch >= 10: break

		// epoch就是遍历正个数据集多少边

- MXNet的高性能数据读取文件格式：rec

类似于TensorFlow的tfrecords，Caffe的Imdb。就是将图片格式化存储为一个二进制文件rec，因为读取小文件会非常非常慢，而读取大文件可加速我们的训练过程。

1. 它的目的都是为了将零碎的图片文件等（不限于图片）格式化为一个连续存储的二进制序列文件，加速训练

2. 官方提供了适用于多数情况下，图片到rec文件的转换工具，Im2rec.py(image to rec)，如果自己从源码编译MXNet可以得到一个C++版本的im2rec可执行文件，但是速度上python版本和c++版本的速度差异不大，主要速度瓶颈在磁盘的IO写rec文件和对原始数据（如图片比较大会读的比较慢）大小上


- 写rec文件，对原始数据（图片等）的要求：

-	图片数据，不同图片的尺寸可以任意大小，也就是说没有限制
-	不仅仅使用于图片，还可支持一般类型的数据，如NumyPy数组
-	可以支持多label，（比如：一个人的身份是什么，ID是什么，性别，年龄）如检测任务中不同Bounding Box的位置信息（4个坐标还有类别，当作不同label进行写入


- im2rec.py的官方使用

	 usage: im2rec.py [-h][--list LIST]...
					  prefix root
	
	 prefix: lst文件所在目录，对该目录下的所有lst文件进行读取，并将其中的图片文件进行转换。lst中定义的是图片的相对路径，加上root就是完整路径
	 root：图片所在根目录
	 以下三个参数很常用：
	 --resize：压缩图片使图片最短边resize成指定大小。一般模型的ssd的图片输入是300*300，而收集原始的图片可能10几M，若是直接读取，那速度会很慢，因为每张图片要读取好几M，而网络的输入又需要300*300.所以没有必要。所以，先要对图片进行压缩。仅是最短边，是变小而不是变形。
	 -- pack-label：如果lst文件中写了多个label，则需要设置为True。
	 -- shuffle：如果要多lst文件进行shuffle后写入rec，则设置为True。就是对输入的文件进行打散，方便后面训练。
	 假设我们现在由100万张图片，那我们需要定义一个类似文本的文件，去告诉我这些文件在哪里，就是说这100万的文件在哪里，每个文件对应的id是多少。这个文件在mxnet中称为lst文件(即.lst文件)

- 用于一般分类任务的图片转换例子（label个数为1）

是一个人脸的数据集合
-	head -n 5 webface.lst
-	tail -n 5 webface.lst

	格式要求：
	1. 每列以tab分隔
	2. 第一列为图片的index，只是为了后续支持随机访问rec读取数据，一般用不到，可以全部设置为0
	3. 最后一列为图片相对路径，prefix，是相对于root的。这样的方便是可以将该lst拷贝到其它电脑上，而不用修改lst文件。只需要指定root就可以啦
	4. 中间列为label，可以多列
	5. lst文件需以.lst作为后缀 


- 转换

	图片根目录： /home/daiab/machine_disk/data/
	lst文件目录：/home/daiab/machine_disk/data/filelst/
	$python im2rec.py /home/daiab/machine_disk/data/filelst/ /home/daiab/machine_disk/data/ --shuffle 1
	生成文件: webface.idx webface.rec
	webface.idx：用于随机读取rec，一般不用，可以删除
	webface.rec：rec目标文件


- MXNet官方提供的常用rec格式数据迭代器
这3个迭代器可以覆盖到90%的需求

1.	ImageRecordIter
一般用于分类任务图片读取，还集成了运行期间的数据增广工作，是一种rec迭代器

2.	ImageDetRecorditer
用于检测任务图片读取与运行期间的数据增广的rec迭代器

3.	BucketSentenceIter
用于补丁长序列数据的迭代器，常用于RNN

- ImageRecordIter例子


		mx.io.ImageRecordIter(
			path_imgrec = 'data.rec' // 完成rec的迭代		
			label_width = 1,
			mean_r = 123.68,
			mean_g = 116.779,
			mean_b = 103.930, // r,g,b的平均值,是预处理功能
			std = , // rgb的标准差
			data_name = 'data',
			label_name = 'softmax_label',
			data_shape = (3, 224, 224),
			batch_size = 128,
			rand_crop = True,

			// 以下是数据的增广
			min_randowm_scale = 1,
			max_randown_scale = 1,
			pad = 0,
			fill_value = 127,
			max_aspect_ratio = 0, # [0, 1]
			random_h = 0, # [0, 180]
			random_s = 0, # [0, 255]
			random_l = 0, # [0, 255]
			max_rotate_angle = 0, # [0, 360]
			max_shear_ratio = 0, # [0, 1]
			rand_mirror = True, # 图片的反转，如人脸时，照镜子和没有照镜子都能识别
			preprocess_trheads = 0, // 调用这个迭代器时需要用多少个线程来处理数据，若IO瓶颈高，就需要更多的thread来读取
			shuffle = True, 
			num_parts = nworker, # kvstore
			part_index = rank) # kvstore


	用于检测任务的跌打器：
	mx.io.ImageDetRecordIter(
		path_imgrec = 'data.rec', // 提供基本的数据
		label_width = -1 # variabl label
		...	
		)


## 2.4 Symbol 
用于符号式编程的接口，符号式的定义只是构建了图的结构，没有立即执行。

	data = nd.ones(shape=(1,2), dtype=np.float32)
	weight = nd.random.normal(shape=(12,2))
	bias = nd.random.normal(shape=(12))
	fc = nd.FullyConnected(data, weight=weight, bias=bias, num_hidden=12)
	print('imperative: ', fc)


	data = mx.sym.Variable('data', shape=(1,2)) 
	fc = mx.sym.FullyConnected(data=data, num_hidden=12)
	print('symbolic: ', fc)

- Symbol基本函数

-	Symbol.infer_type:
-	Symbol.infer_shape:
-	Symbol.list_arguments:
-	Symbol.list_outputs:
-	Symbol.list_auxiliary_states:
















































