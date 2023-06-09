# antlr4-perfopt-test

More detail see PR#4237 https://github.com/antlr/antlr4/pull/4237 

## build antlr4 & generate C++ parser && build Cpp-runtime
```
bash build_all_deps.sh
```

## run coucurrent_perf_test (default lexer & parser)
```
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
make -j8

# test with 1 thread before optimization
./output/concurrent_perf_test 1
# test with 4 threads before optimization
./output/concurrent_perf_test 4
# test with 16 threads before optimization
./output/concurrent_perf_test 16
```

## run concurrent_perf_test (optimized lexer & parser)
```
mkdir build.opt && cd build.opt
cmake .. -DCMAKE_BUILD_TYPE=Release -DENABLE_PR4237_OPT=1
make -j8

# test with 1 thread after optimization
./output/concurrent_perf_test 1
# test with 4 threads after optimization
./output/concurrent_perf_test 4
# test with 16 threads after optimization
./output/concurrent_perf_test 16
```

## expected optimization effect
The trend should be something like the figure below, while the specific numbers may be different.
![image](https://user-images.githubusercontent.com/29702096/235072383-25b6be8f-660b-49e8-a180-984211db55d6.png)


