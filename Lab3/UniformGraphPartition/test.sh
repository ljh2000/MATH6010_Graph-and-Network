# complie
g++ UniformGraphPartition.cpp -o UniformGraphPartition


# test
for num in {1..50}
do
./UniformGraphPartition $num
done

