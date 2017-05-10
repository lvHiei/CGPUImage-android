# CGPUImage-android
GPUImage implements by c++, the android example


# Something not complete
1.GPUImageMaskFilter has some thing not implements


2.GPUImageMosaicFilter the square.png deocode has a question,
the picture has transport, decoding the picture the transport data will
be 0xffffff, the effect is not correct


3.GPUImageSphereRefractionFilter the effect is incorrect, and I don't know why.

The reason is float precision, with hightp float the effect is correct.


4.GPUImagePoissonBlendFilter is not test and the m_uNumIterations is not implement

5.GPUImageLanczosResamplingFilter the originImageSize is not used and
don't know the function of this property.

6.GPUImageGaussianBlurFilter bypasses is not used, the function setBlurRadiusInPixels
is not implements

7.GPUImageVoronoiConsumerFilter the same with GPUImageMosaicFilter

8.GPUImageJFAVoronoiFilter the fiter I don't known how to implements,
the code is incorrect.

9.GPUImageACVFile not support url, only support data array and local file.
It is not tested.

10.GPUImageTiltShiftFilter the effect is incorrect.

10.GPUImageUnsharpMaskFilter the effect is incorrect.