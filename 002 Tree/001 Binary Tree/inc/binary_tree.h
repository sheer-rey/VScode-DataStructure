/*******************************************************************************
 * @file binary_tree.h
 * @author sheer.rey
 * @date Sep.7, 2022
 *
 * @note
 * This pair of files, or, these series of file piars is my personal realization
 * of Data Structure in corresponding learning progress.
 *
 * So tip.1 I hope you know is there may be some slapdash mistake.
 *
 * Another thing is, the reason why I choose to use full english comment is I
 * want to improve my english level by this way.
 *
 * So tip.2 is if you find some grammatical error or others and tell me that
 * I will be very greatful to you! The style of these pair of files may be
 * variable, cause it's also in my C++ learning process, so the programme
 * style may transform C to C++ gradually.
 * ****************************************************************************/

#ifndef _BINARY_TREE_H_
#define _BINARY_TREE_H_

#include <algorithm>
#include <initializer_list>
#include <iostream>
#include <queue>
#include <stack>
#include <stdexcept>
#include <string>
#include <vector>

/* my (sheer.rey) namespace */
namespace libofsheerrey {
  /* binary tree class definition */
  class BinaryTree {
   public:
    /* TreeNode definition */
    struct TreeNode {
      int value{};
      TreeNode* left{};
      TreeNode* right{};
      TreeNode(int value) : value(value) {}
    };

   public:
    /* construct sequence definition */
    enum AnotherSequence { cPreorder, cPostorder };

   private:
    /* data member */
    TreeNode* m_root = nullptr;

   protected:
    /* function member */

    // ↓ construct binary tree with expanded sequence
    TreeNode* ConstructwithExpandedPreorder(
        const std::vector<std::string>& expanded_preorder,
        std::size_t& index,
        bool& construct_error);

    // ↓ construct binary tree with inorder and preorder sequence
    TreeNode* ConstructwithInorderandPreorder(const std::vector<int>& inorder,
                                              std::size_t inorder_begin,
                                              std::size_t inorder_end,
                                              const std::vector<int>& preorder,
                                              std::size_t preorder_begin,
                                              std::size_t preorder_end);

    // ↓ construct binary tree with inorder and postorder sequence
    TreeNode* ConstructwithInorderandPostorder(
        const std::vector<int>& inorder,
        std::size_t inorder_begin,
        std::size_t inorder_end,
        const std::vector<int>& postorder,
        std::size_t postorder_begin,
        std::size_t postorder_end);

    // ↓ construct binary tree with another object
    TreeNode* ConstructwithAnother(const TreeNode* root);

    // ↓ tranversal binary tree
    void PreorderRecursionTraversal(TreeNode* root, std::vector<int>& sequence);
    void InorderRecursionTraversal(TreeNode* root, std::vector<int>& sequence);
    void PostorderRecursionTraversal(TreeNode* root,
                                     std::vector<int>& sequence);
    void PreorderIterationTraversal(std::vector<int>& sequence);
    void InorderIterationTraversal(std::vector<int>& sequence);
    void PostorderIterationTraversal(std::vector<int>& sequence);

    // ↓ destroy binary tree
    void ReleaseAllocatedMemory(TreeNode* root);

   public:
    /* Special member functions */
    // Default Constructor
    BinaryTree() = default;
    // Constructor
    BinaryTree(const std::vector<std::string>& expanded_preorder);
    BinaryTree(const std::vector<int>& inorder_sequence,
               const std::vector<int>& another_sequence,
               AnotherSequence another_sequence_type);
    // Copy Constructor
    BinaryTree(const BinaryTree& binary_tree) {
      m_root = ConstructwithAnother(binary_tree.m_root);
    }
    // Move Constructor
    BinaryTree(BinaryTree&& binary_tree) {
      m_root = binary_tree.m_root;
      binary_tree.m_root = nullptr;
    }
    // Destructor
    ~BinaryTree() { ReleaseAllocatedMemory(m_root); }
    // Copy Operator=
    BinaryTree& operator=(const BinaryTree& binary_tree) {
      if (this != &binary_tree) {
        ReleaseAllocatedMemory(m_root);
        m_root = ConstructwithAnother(binary_tree.m_root);
      }
      return *this;
    }
    // Move Operator=
    BinaryTree& operator=(BinaryTree&& binary_tree) {
      if (this != &binary_tree) {
        ReleaseAllocatedMemory(m_root);
        m_root = binary_tree.m_root;
        binary_tree.m_root = nullptr;
      }
      return *this;
    }

    /* General member functions */
    inline std::vector<int> GetPreorderSequence();
    inline std::vector<int> GetInorderSequence();
    inline std::vector<int> GetPostorderSequence();
    std::vector<int> GetLayerorderSequence();
  };

  /*****************************************************************************
   * @public
   * @name GetPreorderSequence
   * @return an vector that contain the preorder sequence of binary tree
   * @brief traversal binary tree and return the preorder sequence
   * **************************************************************************/
  inline std::vector<int> BinaryTree::GetPreorderSequence() {
    std::vector<int> sequence;

    // recursion traversal
    TreeNode* root = m_root;
    PreorderRecursionTraversal(root, sequence);

    // iteration traversal
    // PreorderIterationTraversal(sequence);

    return sequence;
  }

  /*****************************************************************************
   * @public
   * @name GetInorderSequence
   * @return an vector that contain the inorder sequence of binary tree
   * @brief traversal binary tree and return the inorder sequence
   * **************************************************************************/
  inline std::vector<int> BinaryTree::GetInorderSequence() {
    std::vector<int> sequence;

    // recursion traversal
    TreeNode* root = m_root;
    InorderRecursionTraversal(root, sequence);

    // iteration traversal
    // InorderIterationTraversal(sequence);

    return sequence;
  }

  /*****************************************************************************
   * @public
   * @name GetPostorderSequence
   * @return an vector that contain the postorder sequence of binary tree
   * @brief traversal binary tree and return the postorder sequence
   * **************************************************************************/
  inline std::vector<int> BinaryTree::GetPostorderSequence() {
    std::vector<int> sequence;

    // recursion traversal
    TreeNode* root = m_root;
    PostorderRecursionTraversal(root, sequence);

    // iteration traversal
    // PostorderIterationTraversal(sequence);

    return sequence;
  }

}  // namespace libofsheerrey

#endif