// created by wangtao9
#include <iostream>
#include <thread>
#include <chrono>
#include "antlr4-runtime.h"
#include "generated/CypherLexer.h"
#include "generated/CypherParser.h"
#include "generated/CypherBaseVisitor.h"

using namespace antlr4;
using namespace parser;

const static int QUERY_COUNT = 10000;

const static std::string query_0 = "CALL foo()";
const static std::string query_1 = "RETURN 1";
const static std::string query_2 =
    "MATCH (n:Person {id:2000})-[:knows]->(friend)-[:located_in]->(city) "
    "RETURN friend, count(city) ORDER BY friend.id LIMIT 100";

void proc_pure_parse(int &arg) {
  auto t0 = std::chrono::high_resolution_clock::now();
  for (int i = 0; i < QUERY_COUNT; i++) {
      ANTLRInputStream input(query_2);
      CypherLexer lexer(&input);
      CommonTokenStream tokens(&lexer);
      CypherParser parser(&tokens);
      tree::ParseTree *tree = parser.oC_Cypher();
      CypherBaseVisitor visitor;
      tree->accept(&visitor);
  }
  auto t1 = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0);
  std::cout << duration.count() << "ms\n";
}


void parser_pure_parse_test(int num_thread) {
  std::cout << "[main thread]: " << __func__ << std::endl;
  std::vector<std::thread> threads;
  auto t0 = std::chrono::high_resolution_clock::now();
  for (int i = 0; i < num_thread; i++) {
    threads.emplace_back(proc_pure_parse, std::ref(i));
  }
  // threads join
  for (auto &t : threads) t.join();
  auto t1 = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0);
  std::cout << "[main thread]: " << duration.count() << "ms, "
   << "throughput: " << (double)(QUERY_COUNT * num_thread * 1000) / duration.count() << "/s\n";
}


int main(int argc, const char **argv) {
  if (argc < 2) return 1;
  auto num_thread = atoi(argv[1]);
  parser_pure_parse_test(num_thread);
  return 0;
}

