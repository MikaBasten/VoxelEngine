#pragma once
#include <cmath>
#include <iostream>

struct Vector3f {
    float x, y, z;

    Vector3f(float x, float y, float z) : x(x), y(y), z(z) {}
};

struct Vector3i {
    int x, y, z;

    Vector3i(int x, int y, int z) : x(x), y(y), z(z) {}

    // Overloaded right shift operator
    Vector3i operator>>(const int& shift) const {
        return Vector3i(x >> shift, y >> shift, z >> shift);
    }
};

struct Color {
    float r, g, b;

    Color(float r, float g, float b) : r(r), g(g), b(b) {}
};

struct VoxelData {
    Color color;

    // Default constructor
    VoxelData() : color(0.0f, 0.0f, 0.0f) {}

    // Custom copy constructor
    VoxelData(const VoxelData& other) : color(other.color) {}

    // Custom assignment operator
    VoxelData& operator=(const VoxelData& other) {
        if (this != &other) {
            color = other.color;
        }
        return *this;
    }
};


struct Node {
    bool isLeaf;
    Node* children[8];
    VoxelData data;

    Node() : isLeaf(true) {
        for (int i = 0; i < 8; ++i) {
            children[i] = nullptr;
        }
    }


    // Custom copy constructor
    Node(const Node& other) : isLeaf(other.isLeaf), data(other.data) {
        for (int i = 0; i < 8; ++i) {
            if (other.children[i]) {
                children[i] = new Node(*other.children[i]); // Recursive copy
            }
            else {
                children[i] = nullptr;
            }
        }
    }

    // Destructor
    ~Node() {
        for (int i = 0; i < 8; ++i) {
            delete children[i];
        }
    }

    // Copy assignment operator
    Node& operator=(const Node& other) {
        if (this != &other) {
            isLeaf = other.isLeaf;
            data = other.data;
            for (int i = 0; i < 8; ++i) {
                delete children[i];
                if (other.children[i]) {
                    children[i] = new Node(*other.children[i]); // Recursive copy
                }
                else {
                    children[i] = nullptr;
                }
            }
        }
        return *this;
    }
};

class SparseVoxelOctree {
public:
    SparseVoxelOctree(int size, int maxDepth);

    void Insert(Vector3f point, Color color);
    Node* getRootNode() const;

private:
    void InsertImpl(Node** node, Vector3f point, Color color, Vector3i position, int depth);

    int m_Size;
    int m_MaxDepth;
    Node* m_Root;
};
