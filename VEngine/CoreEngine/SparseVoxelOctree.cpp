#include "SparseVoxelOctree.h"


SparseVoxelOctree::SparseVoxelOctree(int size, int maxDepth)
    : m_Size(size), m_MaxDepth(maxDepth), m_Root(nullptr) {}

void SparseVoxelOctree::Insert(Vector3f point, Color color) {
    Vector3i position(static_cast<int>(std::floor(point.x * m_Size)),
        static_cast<int>(std::floor(point.y * m_Size)),
        static_cast<int>(std::floor(point.z * m_Size)));

    InsertImpl(&m_Root, point, color, position, 0);
}

Node* SparseVoxelOctree::getRootNode() const {
    return m_Root;
}

void SparseVoxelOctree::InsertImpl(Node** node, Vector3f point, Color color, Vector3i position, int depth) {
    if (*node == nullptr) {
        // Create a new node
        *node = new Node();
        (*node)->isLeaf = true;
        for (int i = 0; i < 8; ++i) {
            (*node)->children[i] = nullptr;
        }
    }

    if (depth == m_MaxDepth) {
        // Reached maximum depth, set voxel data
        (*node)->data.color = color;
        // Additional voxel data assignment as needed
    }
    else {
        // Determine octant based on the point's position
        int octant = ((position.x & 1) << 2) | ((position.y & 1) << 1) | (position.z & 1);

        // Recursively insert into the corresponding octant
        InsertImpl(&(*node)->children[octant], point, color, position >> 1, depth + 1);

        // If any child is non-leaf, set the current node as non-leaf
        for (int i = 0; i < 8; ++i) {
            if ((*node)->children[i] && !(*node)->children[i]->isLeaf) {
                (*node)->isLeaf = false;
                break;
            }
        }
    }
}