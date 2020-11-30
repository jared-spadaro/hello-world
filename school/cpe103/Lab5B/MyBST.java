import java.util.*;


public class MyBST extends BST {

  public int height (Node p) {
    if(p==null) return 0;
    return 1+Math.max(height(p.left),height(p.right));
  }

  public boolean isBalanced () {
    return isBalanced(root);
  }
  
  public boolean isBalanced (Node p) {
    boolean balanced = true;
    if(p==null) return true;
    int left = height(p.left);
    int right = height(p.right);
    return isBalanced(p.left) && isBalanced(p.right) && Math.abs(left-right)<2;
  }

}
