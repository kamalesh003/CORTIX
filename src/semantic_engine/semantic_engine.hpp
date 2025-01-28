#pragma once
#include <unordered_map>
#include <string>
#include <vector>
#include <regex>

namespace SemanticEngine {

class BioKG {
private:
    struct Concept {
        std::string id;
        std::unordered_map<std::string, std::vector<std::string>> properties;
    };

    std::unordered_map<std::string, Concept> graph;
    std::unordered_map<std::string, std::vector<std::string>> rules;

    void parse_pattern(const std::string& query);

public:
    void load_ontology(const std::string& ttl_data);
    float evaluate(const std::string& query, 
                   const std::unordered_map<std::string, std::vector<float>>& context);
    void update_knowledge(const std::string& update_query);
    std::vector<float> query(const std::string& sparql, 
                             const std::unordered_map<std::string, std::string>& params);
};

} // namespace SemanticEngine