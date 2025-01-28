#pragma once
#include "../neuromorphic/neuromorphic.hpp"
#include "../semantic_engine/semantic_engine.hpp"

class CortiXProcessor {
private:
    Neuromorphic::SpiNNaker chip;
    SemanticEngine::BioKG knowledge_graph;
    std::unordered_map<std::string, double> patient_context;
    std::string patient_id;

    void process_neural_stream();
    void trigger_intervention(int phase);

public:
    CortiXProcessor(const std::string& patient_id);
    void update_knowledge(const std::string& update_query);
};