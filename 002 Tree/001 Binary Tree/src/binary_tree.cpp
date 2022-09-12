/*******************************************************************************
 * @file binary_tree.cpp
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

#include "binary_tree.h"

/* my (sheer.rey) namespace */
namespace libofsheerrey {
  /* function definition of class BinaryTree */

  /* public member function */

  /*****************************************************************************
   * @public
   * @name BinaryTree
   * @note Constructor
   * @param expanded_preorder expanded preorder sequence of a binary tree
   * @brief Initialize a binary tree with given expanded preorder sequence
   * **************************************************************************/
  BinaryTree::BinaryTree(const std::vector<std::string>& expanded_preorder) {
    // sequence empty check
    if (expanded_preorder.empty()) { return; }

    // construct binary tree with specific input sequence
    bool construct_error = false;
    std::size_t index = 0;
    m_root = ConstructwithExpandedPreorder(expanded_preorder, index,
                                           construct_error);

    // error check
    if (construct_error) {
      // destruct allocated memory
      ReleaseAllocatedMemory(m_root);
    }
  }

  /*****************************************************************************
   * @public
   * @name BinaryTree
   * @note Constructor
   * @param inorder_sequence inorder sequence of a binary tree
   * @param another_sequence another sequence of a binary tree, it can be
   *                         preorder or postorder
   * @param another_sequence_type indicate wether another sequence is preorder
   *                              or postorder, it can be
   *                              BinaryTree::cPreorder or
   *                              BinaryTree::cPostorder
   * @brief Initialize a binary tree with inorder sequence and another sequence
   * @note the \p inorder_sequence and \p another_sequence must be equivalence
   *       and the elements of both must be unique
   * **************************************************************************/
  BinaryTree::BinaryTree(const std::vector<int>& inorder_sequence,
                         const std::vector<int>& another_sequence,
                         AnotherSequence another_sequence_type) {
    /* sequence validity check begin */
    // check size
    if (inorder_sequence.size() != another_sequence.size()) {
      std::cerr << "input sequences are not equivalence!" << std::endl;
      return;
    }

    // duplicate and sort two sequences
    std::vector<int>* seq_1 = new std::vector<int>(inorder_sequence);
    std::vector<int>* seq_2 = new std::vector<int>(another_sequence);
    std::sort(seq_1->begin(), seq_1->end());
    std::sort(seq_2->begin(), seq_2->end());

    // check if two sequences equivalent
    if (!std::equal(seq_1->begin(), seq_1->end(), seq_2->begin())) {
      std::cerr << "input sequences are not equivalence!" << std::endl;
      return;
    }

    // check if elements in sequence unique
    for (std::size_t i = 0; i < seq_1->size() - 1; ++i) {
      if (seq_1[i] == seq_1[i + 1]) {
        std::cerr << "elements in input sequences are not unique!" << std::endl;
      }
    }

    delete seq_1;
    delete seq_2;
    /* sequence validity check end */

    /* construct begin */
    switch (another_sequence_type) {
      case cPreorder:
        m_root = ConstructwithInorderandPreorder(
            inorder_sequence, 0, inorder_sequence.size(), another_sequence, 0,
            another_sequence.size());
        break;

      case cPostorder:
        m_root = ConstructwithInorderandPostorder(
            inorder_sequence, 0, inorder_sequence.size(), another_sequence, 0,
            another_sequence.size());
        break;

      default:
        std::cerr << "invalid parameter: another_sequence_type!" << std::endl;
        break;
    }
    /* construct end */
  }

  /*****************************************************************************
   * @public
   * @name GetLayerorderSequence
   * @return an vector that contain the layerorder sequence of binary tree
   * @brief traversal binary tree and return the layerorder sequence
   * **************************************************************************/
  std::vector<int> BinaryTree::GetLayerorderSequence() {
    std::vector<int> sequence;
    std::queue<TreeNode*> nodes;
    nodes.push(m_root);

    TreeNode* node;
    while (nodes.size()) {
      node = nodes.front(), nodes.pop();
      sequence.push_back(node->value);
      if (node->left) { nodes.push(node->left); }
      if (node->right) { nodes.push(node->right); }
    }

    return sequence;
  }

  /*****************************************************************************
   * @protected
   * @name ConstructwithExpandedPreorder
   * @note Using for Constructor
   * @param expanded_preorder expanded preorder sequence of a binary tree
   * @param index the index of current node in sequence
   * @param construct_error indicate wether error occured in construct process
   * @brief recurrence construct binary tree with expanded preorder sequence
   * **************************************************************************/
  BinaryTree::TreeNode* BinaryTree::ConstructwithExpandedPreorder(
      const std::vector<std::string>& expanded_preorder,
      std::size_t& index,
      bool& construct_error) {
    // termination condition
    if (index >= expanded_preorder.size() || construct_error) {
      return nullptr;
    }

    // null node or error check
    int value;
    try {
      value = std::stoi(expanded_preorder[index]);
    } catch (const std::invalid_argument& e) {
      // expanded_preorder[index] is not a integer, consider it as null node
      ++index;
      return nullptr;
    } catch (const std::exception& e) {
      // other errors
      std::cerr << "Unknown error occured: " << e.what() << std::endl;
      construct_error = true;
      return nullptr;
    }

    // ↓ preorder traversal
    TreeNode* root = new TreeNode(value);
    ++index;
    root->left = ConstructwithExpandedPreorder(expanded_preorder, index,
                                               construct_error);
    root->right = ConstructwithExpandedPreorder(expanded_preorder, index,
                                                construct_error);
    return root;
  }

  /*****************************************************************************
   * @protected
   * @name ConstructwithInorderandPreorder
   * @note Using for Constructor
   * @param inorder the inorder sequence of a binary tree
   * @param inorder_begin the begin index of inorder sequence in a subtree
   * @param inorder_end the end index of inorder sequence in a subtree
   * @param preorder the preorder sequence of a binary tree
   * @param preorder_begin the begin index of preorder sequence in a subtree
   * @param preorder_end the end index of preorder sequence in a subtree
   * @note the range btween \p begin and \p end is the left closed and right
   *       open interval : [begin, end)
   * @brief recurrence construct binary tree with inorder and preorder sequence
   * **************************************************************************/
  BinaryTree::TreeNode* BinaryTree::ConstructwithInorderandPreorder(
      const std::vector<int>& inorder,
      std::size_t inorder_begin,
      std::size_t inorder_end,
      const std::vector<int>& preorder,
      std::size_t preorder_begin,
      std::size_t preorder_end) {
    // terminate condition
    if (inorder_begin == inorder_end) { return nullptr; }

    // get root node and its index in current sequence pair
    TreeNode* root = new TreeNode(preorder[preorder_begin]);
    std::size_t root_index_in_inorder;
    for (std::size_t i = inorder_begin; i < inorder_end; ++i) {
      if (inorder[i] == root->value) { root_index_in_inorder = i; }
    }
    std::size_t left_subtree_lenth = root_index_in_inorder - inorder_begin;

    // recurrence
    root->left = ConstructwithInorderandPreorder(
        inorder, inorder_begin, root_index_in_inorder, preorder,
        preorder_begin + 1, preorder_begin + 1 + left_subtree_lenth);
    root->right = ConstructwithInorderandPreorder(
        inorder, root_index_in_inorder + 1, inorder_end, preorder,
        preorder_begin + 1 + left_subtree_lenth, preorder_end);
    return root;
  }

  /*****************************************************************************
   * @protected
   * @name ConstructwithInorderandPostorder
   * @note Using for Constructor
   * @param inorder the inorder sequence of a binary tree
   * @param inorder_begin the begin index of inorder sequence in a subtree
   * @param inorder_end the end index of inorder sequence in a subtree
   * @param postorder the postorder sequence of a binary tree
   * @param postorder_begin the begin index of postorder sequence in a subtree
   * @param postorder_end the end index of postorder sequence in a subtree
   * @note the range btween \p begin and \p end is the left closed and right
   *       open interval : [begin, end)
   * @brief recurrence construct binary tree with inorder and postorder sequence
   * **************************************************************************/
  BinaryTree::TreeNode* BinaryTree::ConstructwithInorderandPostorder(
      const std::vector<int>& inorder,
      std::size_t inorder_begin,
      std::size_t inorder_end,
      const std::vector<int>& postorder,
      std::size_t postorder_begin,
      std::size_t postorder_end) {
    // terminate condition
    if (inorder_begin == inorder_end) { return nullptr; }

    // get root node and its index in current sequence pair
    TreeNode* root = new TreeNode(postorder[postorder_end - 1]);
    std::size_t root_index_in_inorder;
    for (std::size_t i = inorder_begin; i < inorder_end; ++i) {
      if (inorder[i] == root->value) { root_index_in_inorder = i; }
    }
    std::size_t left_subtree_lenth = root_index_in_inorder - inorder_begin;

    // recurrence
    root->left = ConstructwithInorderandPostorder(
        inorder, inorder_begin, root_index_in_inorder, postorder,
        postorder_begin, postorder_begin + left_subtree_lenth);
    root->right = ConstructwithInorderandPostorder(
        inorder, root_index_in_inorder + 1, inorder_end, postorder,
        postorder_begin + left_subtree_lenth, postorder_end - 1);
    return root;
  }

  /*****************************************************************************
   * @protected
   * @name ConstructwithAnother
   * @note Using for copy constructor
   * @param root Another BinaryTree object's root node
   * @brief Recurrence construct an binary tree with another exist one
   * **************************************************************************/
  BinaryTree::TreeNode* BinaryTree::ConstructwithAnother(const TreeNode* root) {
    // terminate condition
    if (root == nullptr) { return nullptr; }

    // preorder traversal
    TreeNode* new_root = new TreeNode(root->value);
    new_root->left = ConstructwithAnother(root->left);
    new_root->right = ConstructwithAnother(root->right);
    return new_root;
  }

  /*****************************************************************************
   * @protected
   * @name ReleaseAllocatedMemory
   * @param root root node of a binary tree
   * @brief recurrence destroy binary tree
   * **************************************************************************/
  void BinaryTree::ReleaseAllocatedMemory(TreeNode* root) {
    // terminate condition
    if (root == nullptr) { return; }

    // release allocated memory in postorder
    ReleaseAllocatedMemory(root->left);
    ReleaseAllocatedMemory(root->right);
    delete root;
    root = nullptr;
  }

  /*****************************************************************************
   * @protected
   * @name PreorderRecursionTraversal
   * @param root root node of a binary tree
   * @param sequence returned preorder sequence, must be a empty vector
   * @brief recurrence preorder traverse binary tree and get the sequence
   * **************************************************************************/
  void BinaryTree::PreorderRecursionTraversal(TreeNode* root,
                                              std::vector<int>& sequence) {
    // terminate condition
    if (root == nullptr) { return; }

    // preorder traversal
    sequence.push_back(root->value);
    PreorderRecursionTraversal(root->left, sequence);
    PreorderRecursionTraversal(root->right, sequence);
  }

  /*****************************************************************************
   * @protected
   * @name InorderRecursionTraversal
   * @param root root node of a binary tree
   * @param sequence returned inorder sequence, must be a empty vector
   * @brief recurrence inorder traverse binary tree and get the sequence
   * **************************************************************************/
  void BinaryTree::InorderRecursionTraversal(TreeNode* root,
                                             std::vector<int>& sequence) {
    // terminate condition
    if (root == nullptr) { return; }

    // inorder traversal
    InorderRecursionTraversal(root->left, sequence);
    sequence.push_back(root->value);
    InorderRecursionTraversal(root->right, sequence);
  }

  /*****************************************************************************
   * @protected
   * @name PostorderRecursionTraversal
   * @param root root node of a binary tree
   * @param sequence returned postorder sequence, must be a empty vector
   * @brief recurrence postorder traverse binary tree and get the sequence
   * **************************************************************************/
  void BinaryTree::PostorderRecursionTraversal(TreeNode* root,
                                               std::vector<int>& sequence) {
    // terminate condition
    if (root == nullptr) { return; }

    // preorder traversal
    PostorderRecursionTraversal(root->left, sequence);
    PostorderRecursionTraversal(root->right, sequence);
    sequence.push_back(root->value);
  }

  /*****************************************************************************
   * @protected
   * @name PreorderIterationTraversal
   * @param sequence returned preorder sequence, must be a empty vector
   * @brief Iterated preorder traverse binary tree and get the sequence
   * **************************************************************************/
  void BinaryTree::PreorderIterationTraversal(std::vector<int>& sequence) {
    std::stack<TreeNode*> traversal_stack;
    if (m_root) { traversal_stack.push(m_root); }

    TreeNode* node;
    while (traversal_stack.size()) {
      node = traversal_stack.top(), traversal_stack.pop();

      if (node) {
        if (node->right) { traversal_stack.push(node->right); }
        if (node->left) { traversal_stack.push(node->left); }
        traversal_stack.push(node), traversal_stack.push(nullptr);
      } else {
        node = traversal_stack.top(), traversal_stack.pop();
        sequence.push_back(node->value);
      }
    }
  }

  /*****************************************************************************
   * @protected
   * @name InorderIterationTraversal
   * @param sequence returned inorder sequence, must be a empty vector
   * @brief Iterated inorder traverse binary tree and get the sequence
   * **************************************************************************/
  void BinaryTree::InorderIterationTraversal(std::vector<int>& sequence) {
    std::stack<TreeNode*> traversal_stack;
    if (m_root) { traversal_stack.push(m_root); }

    TreeNode* node;
    while (traversal_stack.size()) {
      node = traversal_stack.top(), traversal_stack.pop();

      if (node) {
        if (node->right) { traversal_stack.push(node->right); }
        traversal_stack.push(node), traversal_stack.push(nullptr);
        if (node->left) { traversal_stack.push(node->left); }
      } else {
        node = traversal_stack.top(), traversal_stack.pop();
        sequence.push_back(node->value);
      }
    }
  }

  /*****************************************************************************
   * @protected
   * @name PostorderIterationTraversal
   * @param sequence returned postorder sequence, must be a empty vector
   * @brief Iterated postorder traverse binary tree and get the sequence
   * **************************************************************************/
  void BinaryTree::PostorderIterationTraversal(std::vector<int>& sequence) {
    std::stack<TreeNode*> traversal_stack;
    if (m_root) { traversal_stack.push(m_root); }

    TreeNode* node;
    while (traversal_stack.size()) {
      node = traversal_stack.top(), traversal_stack.pop();

      if (node) {
        traversal_stack.push(node), traversal_stack.push(nullptr);
        if (node->right) { traversal_stack.push(node->right); }
        if (node->left) { traversal_stack.push(node->left); }
      } else {
        node = traversal_stack.top(), traversal_stack.pop();
        sequence.push_back(node->value);
      }
    }
  }

}  // namespace libofsheerrey