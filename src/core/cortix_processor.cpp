#include "cortix_processor.hpp"
#include <thread>

CortiXProcessor::CortiXProcessor(const std::string& patient_id) 
    : patient_id(patient_id) {
    knowledge_graph.load_ontology("epilepsy_ontology.ttl");
    std::thread(&CortiXProcessor::process_neural_stream, this).detach();
}

void CortiXProcessor::process_neural_stream() {
    while (true) {
        auto spikes = chip.get_spike_stream()->read(10);
        std::vector<float> features;
        for (const auto& s : spikes) features.push_back(s.amplitude);
        
        auto prediction = chip.snn_predict(features);
        float risk = knowledge_graph.evaluate(
            "SeizureRiskAssessment", 
            {{"features", features}, {"stress_level", {0.7f}}}
        );
        
        if (risk > 0.8f) {
            trigger_intervention(prediction.predicted_phase);
        }
    }
}

void CortiXProcessor::trigger_intervention(int phase) {
    auto params = knowledge_graph.query(
        "EmergencyStimulationProtocol", 
        {{"phase", std::to_string(phase)}}
    );
    chip.apply_stimulation(params);
}

void CortiXProcessor::update_knowledge(const std::string& update_query) {
    knowledge_graph.update_knowledge(update_query);
}