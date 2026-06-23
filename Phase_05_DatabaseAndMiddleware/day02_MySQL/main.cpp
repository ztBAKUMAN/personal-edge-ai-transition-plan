#include <iostream>

int main() {
    std::cout << "MySQL Integration for Edge AI\n\n";
    std::cout << "Use cases:\n";
    std::cout << "  - Inference result logging\n";
    std::cout << "  - Model version management\n";
    std::cout << "  - Device/edge node registry\n\n";

    std::cout << "C++ connectors:\n";
    std::cout << "  libmysqlclient (MySQL C API)\n";
    std::cout << "  mysql-connector-cpp (official C++)\n";
    std::cout << "  SOCI (cross-database abstraction)\n\n";

    std::cout << "Schema example:\n";
    std::cout << "  CREATE TABLE inference_log (\n";
    std::cout << "    id INT AUTO_INCREMENT PRIMARY KEY,\n";
    std::cout << "    device_id VARCHAR(64),\n";
    std::cout << "    model_name VARCHAR(128),\n";
    std::cout << "    latency_ms FLOAT,\n";
    std::cout << "    confidence FLOAT,\n";
    std::cout << "    timestamp DATETIME DEFAULT CURRENT_TIMESTAMP\n";
    std::cout << "  );\n";
    return 0;
}
