
# build wangtao9/antlr4
TOP_LEVEL_DIR=${PWD}
git clone https://github.com/wangtao9/antlr4.git
cd antlr4 && git checkout -b fix_cpp_leak_risk origin/fix_cpp_leak_risk && mvn -DskipTests install


# generate cpp lexer & parser
cd $TOP_LEVEL_DIR
ANTLR4_JAR=${PWD}/antlr4/tool/target/antlr4-4.12.1-SNAPSHOT-complete.jar
java -jar ${ANTLR4_JAR} -Dlanguage=Cpp -visitor -o src/generated -package parser Cypher.g4


# build antlr4-cpp-runtime
# see https://github.com/antlr/antlr4/tree/master/runtime/Cpp
cd antlr4/runtime/Cpp
mkdir build && mkdir run && cd build
cmake .. -DCMAKE_BUILD_TYPE=Debug -DWITH_DEMO=0
make -j8
DESTDIR=../run make install
cd ../run/usr/local/ && ln -s lib lib64


