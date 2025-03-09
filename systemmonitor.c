// #define PY_SSIZE_T_CLEAN
// #include <Python.h>
// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <unistd.h>


// // Function to get the CPU usage
// static PyObject* get_cpu_usage(PyObject* self, PyObject* args) {
//     FILE* file = fopen("/proc/stat", "r");
//     if (file == NULL) {
//         PyErr_SetString(PyExc_RuntimeError, "Failed to open /proc/stat");
//         return NULL;
//     }

//     long user, nice, system, idle, iowait, irq, softirq, steal;
//     fscanf(file, "cpu %ld %ld %ld %ld %ld %ld %ld %ld", &user, &nice, &system, &idle, &iowait, &irq, &softirq, &steal);
//     fclose(file);

//     long total_idle = idle + iowait;
//     long total_non_idle = user + nice + system + irq + softirq + steal;
//     long total = total_idle + total_non_idle;

//     sleep(1);

//     file = fopen("/proc/stat", "r");
//     if (file == NULL) {
//         PyErr_SetString(PyExc_RuntimeError, "Failed to open /proc/stat");
//         return NULL;
//     }

//     long user2, nice2, system2, idle2, iowait2, irq2, softirq2, steal2;
//     fscanf(file, "cpu %ld %ld %ld %ld %ld %ld %ld %ld", &user2, &nice2, &system2, &idle2, &iowait2, &irq2, &softirq2, &steal2);
//     fclose(file);

//     long total_idle2 = idle2 + iowait2;
//     long total_non_idle2 = user2 + nice2 + system2 + irq2 + softirq2 + steal2;
//     long total2 = total_idle2 + total_non_idle2;

//     long total_diff = total2 - total;
//     long total_idle_diff = total_idle2 - total_idle;

//     double cpu_usage = (double)(total_diff - total_idle_diff) / total_diff * 100;

//     return Py_BuildValue("d", cpu_usage);
// }

// // Function to get the memory usage
// static PyObject* get_memory_usage(PyObject* self, PyObject* args) {
//     FILE* file = fopen("/proc/meminfo", "r");
//     if (file == NULL) {
//         PyErr_SetString(PyExc_RuntimeError, "Failed to open /proc/meminfo");
//         return NULL;
//     }

//     char line[256];
//     long total_memory = 0;
//     long free_memory = 0;
//     long buffers = 0;
//     long cached = 0;
//     while (fgets(line, sizeof(line), file)) {
//         if (strstr(line, "MemTotal:") == line) {
//             sscanf(line, "MemTotal: %ld kB", &total_memory);
//         } else if (strstr(line, "MemFree:") == line) {
//             sscanf(line, "MemFree: %ld kB", &free_memory);
//         } else if (strstr(line, "Buffers:") == line) {
//             sscanf(line, "Buffers: %ld kB", &buffers);
//         } else if (strstr(line, "Cached:") == line) {
//             sscanf(line, "Cached: %ld kB", &cached);
//         }
//     }
//     fclose(file);

//     long used_memory = total_memory - free_memory - buffers - cached;
//     double memory_usage = (double)used_memory / total_memory * 100;

//     return Py_BuildValue("d", memory_usage);
// }

// // Function to get the network usage
// static PyObject* get_network_usage(PyObject* self, PyObject* args) {
//     FILE* file = fopen("/proc/net/dev", "r");
//     if (file == NULL) {
//         PyErr_SetString(PyExc_RuntimeError, "Failed to open /proc/net/dev");
//         return NULL;
//     }

//     char line[256];
//     long rx_bytes = 0;
//     long tx_bytes = 0;

//     // Skip the first two lines
//     fgets(line, sizeof(line), file);
//     fgets(line, sizeof(line), file);

//     while (fgets(line, sizeof(line), file)) {
//         char interface[32];
//         long rx_bytes, tx_bytes;
//         sscanf(line, "%s %ld %*d %*d %*d %*d %*d %*d %*d %ld", interface, &rx_bytes, &tx_bytes);
        
//         if (strstr(interface, "lo:") == NULL) {
//             rx_bytes += rx_bytes;
//             tx_bytes += tx_bytes;
//         }
        
//     }
//     fclose(file);

//     long initial_rx_bytes = rx_bytes;
//     long initial_tx_bytes = tx_bytes;

//     sleep(1);

//     file = fopen("/proc/net/dev", "r");
//     if (file == NULL) {
//         PyErr_SetString(PyExc_RuntimeError, "Failed to open /proc/net/dev");
//         return NULL;
//     }

//     // Skip the first two lines
//     fgets(line, sizeof(line), file);
//     fgets(line, sizeof(line), file);

//     rx_bytes = 0;
//     tx_bytes = 0;

//     while (fgets(line, sizeof(line), file)) {
//         char interface[32];
//         long rx_bytes, tx_bytes;
//         sscanf(line, "%s %ld %*d %*d %*d %*d %*d %*d %*d %ld", interface, &rx_bytes, &tx_bytes);
        
//         if (strstr(interface, "lo:") == NULL) {
//             rx_bytes += rx_bytes;
//             tx_bytes += tx_bytes;
//         }
        
//     }
//     fclose(file);

//     long rx_bytes_diff = rx_bytes - initial_rx_bytes;
//     long tx_bytes_diff = tx_bytes - initial_tx_bytes;

//     double rx_speed = (double)rx_bytes_diff / 1024;

//     return Py_BuildValue("d", rx_speed);
// }

// // method definitions
// static PyMethodDef SystemMonitorMethods[] = {
//     {"get_cpu_usage", get_cpu_usage, METH_NOARGS, "Get the CPU usage"},
//     {"get_memory_usage", get_memory_usage, METH_NOARGS, "Get the memory usage"},
//     {"get_network_usage", get_network_usage, METH_NOARGS, "Get the network usage"},
//     {NULL, NULL, 0, NULL}
// };

// // module definition
// static struct PyModuleDef systemmonitormodule = {
//     PyModuleDef_HEAD_INIT,
//     "systemmonitor",
//     "A module to get system information",
//     -1,
//     SystemMonitorMethods
// };

// // module initialization
// PyMODINIT_FUNC PyInit_systemmonitor(void) {
//     return PyModule_Create(&systemmonitormodule);
// }


#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// Function to get the CPU usage
static PyObject* get_cpu_usage(PyObject* self, PyObject* args) {
    FILE* file = fopen("/proc/stat", "r");
    if (file == NULL) {
        PyErr_SetString(PyExc_RuntimeError, "Failed to open /proc/stat");
        return NULL;
    }

    long user, nice, system, idle, iowait, irq, softirq, steal;
    if (fscanf(file, "cpu %ld %ld %ld %ld %ld %ld %ld %ld", 
               &user, &nice, &system, &idle, &iowait, &irq, &softirq, &steal) != 8) {
        fclose(file);
        PyErr_SetString(PyExc_RuntimeError, "Failed to parse CPU data");
        return NULL;
    }
    fclose(file);

    long total_idle = idle + iowait;
    long total_non_idle = user + nice + system + irq + softirq + steal;
    long total = total_idle + total_non_idle;

    sleep(1);

    file = fopen("/proc/stat", "r");
    if (file == NULL) {
        PyErr_SetString(PyExc_RuntimeError, "Failed to open /proc/stat");
        return NULL;
    }

    long user2, nice2, system2, idle2, iowait2, irq2, softirq2, steal2;
    if (fscanf(file, "cpu %ld %ld %ld %ld %ld %ld %ld %ld", 
               &user2, &nice2, &system2, &idle2, &iowait2, &irq2, &softirq2, &steal2) != 8) {
        fclose(file);
        PyErr_SetString(PyExc_RuntimeError, "Failed to parse CPU data");
        return NULL;
    }
    fclose(file);

    long total_idle2 = idle2 + iowait2;
    long total_non_idle2 = user2 + nice2 + system2 + irq2 + softirq2 + steal2;
    long total2 = total_idle2 + total_non_idle2;

    long total_diff = total2 - total;
    long total_idle_diff = total_idle2 - total_idle;

    double cpu_usage = (double)(total_diff - total_idle_diff) / total_diff * 100;

    return Py_BuildValue("d", cpu_usage);
}

// Function to get the memory usage
static PyObject* get_memory_usage(PyObject* self, PyObject* args) {
    FILE* file = fopen("/proc/meminfo", "r");
    if (file == NULL) {
        PyErr_SetString(PyExc_RuntimeError, "Failed to open /proc/meminfo");
        return NULL;
    }

    char line[256];
    long total_memory = 0;
    long free_memory = 0;
    long buffers = 0;
    long cached = 0;
    
    while (fgets(line, sizeof(line), file) != NULL) {
        if (strstr(line, "MemTotal:") == line) {
            if (sscanf(line, "MemTotal: %ld kB", &total_memory) != 1) {
                // Handle parsing error
            }
        } else if (strstr(line, "MemFree:") == line) {
            if (sscanf(line, "MemFree: %ld kB", &free_memory) != 1) {
                // Handle parsing error
            }
        } else if (strstr(line, "Buffers:") == line) {
            if (sscanf(line, "Buffers: %ld kB", &buffers) != 1) {
                // Handle parsing error
            }
        } else if (strstr(line, "Cached:") == line) {
            if (sscanf(line, "Cached: %ld kB", &cached) != 1) {
                // Handle parsing error
            }
        }
    }
    fclose(file);

    long used_memory = total_memory - free_memory - buffers - cached;
    double memory_usage = (double)used_memory / total_memory * 100;

    return Py_BuildValue("d", memory_usage);
}

// Function to get the network usage
static PyObject* get_network_usage(PyObject* self, PyObject* args) {
    FILE* file = fopen("/proc/net/dev", "r");
    if (file == NULL) {
        PyErr_SetString(PyExc_RuntimeError, "Failed to open /proc/net/dev");
        return NULL;
    }

    char line[256];
    long total_rx_bytes = 0;
    long total_tx_bytes = 0;

    // Skip the first two lines
    if (fgets(line, sizeof(line), file) == NULL || 
        fgets(line, sizeof(line), file) == NULL) {
        fclose(file);
        PyErr_SetString(PyExc_RuntimeError, "Failed to read header lines from /proc/net/dev");
        return NULL;
    }

    while (fgets(line, sizeof(line), file) != NULL) {
        char interface[32];
        long rx, tx;
        
        if (sscanf(line, "%s %ld %*d %*d %*d %*d %*d %*d %*d %ld", interface, &rx, &tx) >= 2) {
            // Skip loopback interface
            if (strstr(interface, "lo:") == NULL) {
                total_rx_bytes += rx;
                total_tx_bytes += tx;
            }
        }
    }
    fclose(file);

    long initial_rx_bytes = total_rx_bytes;
    long initial_tx_bytes = total_tx_bytes;

    sleep(1);

    file = fopen("/proc/net/dev", "r");
    if (file == NULL) {
        PyErr_SetString(PyExc_RuntimeError, "Failed to open /proc/net/dev");
        return NULL;
    }

    // Skip the first two lines
    if (fgets(line, sizeof(line), file) == NULL || 
        fgets(line, sizeof(line), file) == NULL) {
        fclose(file);
        PyErr_SetString(PyExc_RuntimeError, "Failed to read header lines from /proc/net/dev");
        return NULL;
    }

    total_rx_bytes = 0;
    total_tx_bytes = 0;

    while (fgets(line, sizeof(line), file) != NULL) {
        char interface[32];
        long rx, tx;
        
        if (sscanf(line, "%s %ld %*d %*d %*d %*d %*d %*d %*d %ld", interface, &rx, &tx) >= 2) {
            // Skip loopback interface
            if (strstr(interface, "lo:") == NULL) {
                total_rx_bytes += rx;
                total_tx_bytes += tx;
            }
        }
    }
    fclose(file);

    long rx_bytes_diff = total_rx_bytes - initial_rx_bytes;
    long tx_bytes_diff = total_tx_bytes - initial_tx_bytes;

    // Convert to KB/s for a more reasonable scale
    double network_speed = (double)(rx_bytes_diff + tx_bytes_diff) / 1024;

    return Py_BuildValue("d", network_speed);
}

// method definitions
static PyMethodDef SystemMonitorMethods[] = {
    {"get_cpu_usage", get_cpu_usage, METH_NOARGS, "Get the CPU usage"},
    {"get_memory_usage", get_memory_usage, METH_NOARGS, "Get the memory usage"},
    {"get_network_usage", get_network_usage, METH_NOARGS, "Get the network usage"},
    {NULL, NULL, 0, NULL}
};

// module definition
static struct PyModuleDef systemmonitormodule = {
    PyModuleDef_HEAD_INIT,
    "systemmonitor",
    "A module to get system information",
    -1,
    SystemMonitorMethods
};

// module initialization
PyMODINIT_FUNC PyInit_systemmonitor(void) {
    return PyModule_Create(&systemmonitormodule);
}