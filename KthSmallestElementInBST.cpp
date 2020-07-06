/*
  Finding Kth smallest element in BST.
  Given K, find kth smallest element in BST.
  Classic approach would be to use recursion in order to visit inorder the BST, and at the K'th visition return the visited node data.
  Complexity will be - run time complexity: O(K) <= O(N), Space complexity - the stack used for the recursion - O(K) <= O(N).
  However, space complexity can be reduced to a constant O(1) using morris traversal.
  The idea is as follows: when trying to decide for node N (=Current in the code) to either visit it or not we need to consider it's inorder position.
  * if N is indeed at the inorder postion then it will have no left child, and thus we can consider N as visited and progress N to point to the root of the right subtree.
  * if N is NOT at the inorder postion, then it has a left-child and therefore left subtree, on the LeftSubtree(N) we must find right-most node R-M = RightMostNode(LeftSubtree(N))
    such that the right child of R-M is either NULL or the right child of R-M is N (if the right child was N, then, N was visited before)
    * if Right child of R-M=Right(R-M) is NULL, then we will create a link to N from the right-edge of R-M - this will allow to return to previous levels of the tree, then, we progress N to point to be the root of the left subtree.
    * else ( Right(R-M) was N), so we do 2 things:
        1) we remove the link to the previous N by setting the right edge of R-M to NULL
        2) N is in inorder position (since we traversed a cycle that started from N via some link that was created in some previous iteration), so we can consider N as visited, then, we progress N to point to the root of the right subtree.
  we do this while N is pointing to some not empty subtree.
  With a small modification we track the number of vistions made and when the number is equal K, we can break the algorithm and return data(N). This may break the tree structure.
  To maintain the tree structure we update the kth smallest element with this value and allow the algorithm to move through the entire tree (this will maintain the tree structure, because the links are deleted after a single cyclic traversal).
  Since we gave up on the stack, but created edge the complexity have changed as follows:
  Space complexity is now reduced to a constant: O(1)
  Run time complexity is now at most O(2N) (if the tree is actually a path given by left-children only) = O(N).
*/
// Return the Kth smallest element in the given BST 
int CustomMorrisTraversal(Node *root ,int K){
    int in_order_cnt = 0;
    Node * current = root;
    int  kth = -1;
    while(current != NULL){
        if(current->left == NULL){
            in_order_cnt++;
            if(in_order_cnt == K){
                 kth = current->data;
            }
            current = current->right;
        }
        else {
            Node * pre_to_current = current->left;
            while(pre_to_current->right && pre_to_current->right != current)
                pre_to_current = pre_to_current->right;
            if(pre_to_current->right == NULL){
                pre_to_current->right = current;
                current = current->left;
            }
            else {
                pre_to_current->right = NULL;
                in_order_cnt++;
                if(in_order_cnt == K)
                    kth = current->data;
                current = current->right;
            }
            
        }
    }
    return kth;
    
}
int KthSmallestElement(Node *root, int K)
{
    //add code here.
    return CustomMorrisTraversal(root,K);
}
