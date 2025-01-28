#include "semantic_engine.hpp"
#include <iostream>

namespace SemanticEngine {

void BioKG::parse_pattern(const std::string& query) {
    std::regex relation_re(R"((\w+)\s*:\s*(\w+))");
    std::smatch matches;
    if (std::regex_search(query, matches, relation_re)) {
        std::string subject = matches[1];
        std::string predicate = matches[2];
        rules[subject].push_back(predicate);
    }
}

void BioKG::load_ontology(const std::string& ttl_data) {
    std::regex triple_re(R"((\w+)\s+(\w+)\s+(\w+))");
    std::sregex_iterator it(ttl_data.begin(), ttl_data.end(), triple_re);
    std::sregex_iterator end;
    while (it != end) {
        Concept c;
        c.id = (*it)[1];
        c.properties[(*it)[2]].push_back((*it)[3]);
        graph[c.id] = c;
        ++it;
    }
}

float BioKG::evaluate(const std::string& query, 
                      const std::unordered_map<std::string, std::vector<float>>& context) {
    float risk_score = 0.0f;
    if (query.find("Seizure") != std::string::npos) {
        if (context.count("features")) {
            for (auto f : context.at("features")) risk_score += f * 0.1f;
        }
        if (context.count("stress_level")) {
            risk_score += context.at("stress_level")[0] * 0.3f;
        }
    }
    return std::min(1.0f, risk_score);
}

void BioKG::update_knowledge(const std::string& update_query) {
    parse_pattern(update_query);
    if (update_query.find("StressLevel") != std::string::npos) {
        graph["Patient"].properties["risk_factors"].push_back("Stress");
    }
}

std::vector<float> BioKG::query(const std::string& sparql, 
                                const std::unordered_map<std::string, std::string>& params) {
    if (sparql.find("Stimulation") != std::string::npos) {
        return {130.0f, 0.5f, 100.0f};
    }
    return {};
}

} // namespace SemanticEngine