#pragma once
#include <vector>
#include <queue>
#include <thread>
#include <atomic>
#include <functional>
#include <mutex>

namespace Neuromorphic {

struct SpikeEvent {
    uint64_t timestamp;
    uint16_t channel;
    float amplitude;
};

class SpikeStream {
private:
    std::queue<SpikeEvent> buffer;
    std::mutex buffer_mutex;
    std::atomic<bool> running{true};
    
public:
    void push(const SpikeEvent& event);
    std::vector<SpikeEvent> read(size_t max_events);
    void stop();
};

struct SNNConfig {
    float threshold = 0.8f;
    float leak = 0.1f;
    size_t input_channels = 64;
    size_t hidden_neurons = 128;
};

class SpiNNaker {
private:
    SNNConfig config;
    SpikeStream stream;
    std::vector<float> neuron_weights;
    std::thread processor_thread;
    std::atomic<bool> running{true}; // Add running flag

    void lif_neuron_processor();

public:
    SpiNNaker();
    ~SpiNNaker();

    SpikeStream* get_spike_stream(); 
    struct PredictionResult {
        float confidence;
        int predicted_phase;
        uint64_t estimated_onset;
    };

    PredictionResult snn_predict(const std::vector<float>& features);
    void apply_stimulation(const std::vector<float>& params);
    void reconfigure(const SNNConfig& new_config);
};

} // namespace Neuromorphic