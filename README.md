The binary format of this datasets should be the same that in http://yann.lecun.com/exdb/mnist/

The code that produces them is in app.cpp. To compile it just do g++ app.cpp -o app.

To convert a dataset just do
> ./app t10k-images-idx3-ubyte
> ./app train-images-idx3-ubyte

it will produce the corresponding file with 14x14 at the end of the file
