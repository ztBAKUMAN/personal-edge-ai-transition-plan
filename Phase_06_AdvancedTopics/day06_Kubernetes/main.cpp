#include <iostream>

int main() {
    std::cout << "Kubernetes for Edge AI Orchestration\n\n";
    std::cout << "K3s — Lightweight Kubernetes for Edge:\n";
    std::cout << "  curl -sfL https://get.k3s.io | sh -\n\n";

    std::cout << "Deployment example:\n";
    std::cout << "  apiVersion: apps/v1\n";
    std::cout << "  kind: Deployment\n";
    std::cout << "  metadata:\n";
    std::cout << "    name: edge-inference\n";
    std::cout << "  spec:\n";
    std::cout << "    replicas: 1\n";
    std::cout << "    template:\n";
    std::cout << "      spec:\n";
    std::cout << "        containers:\n";
    std::cout << "        - name: inference\n";
    std::cout << "          image: edge-ai:latest\n";
    std::cout << "          resources:\n";
    std::cout << "            limits:\n";
    std::cout << "              nvidia.com/gpu: 1\n\n";

    std::cout << "Why K8s on edge:\n";
    std::cout << "  1. OTA update / rollback\n";
    std::cout << "  2. Resource limit (CPU/memory)\n";
    std::cout << "  3. Health check + auto-restart\n";
    std::cout << "  4. Multi-node orchestration\n";
    return 0;
}
