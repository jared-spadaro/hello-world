

public class MyBST extends BST {

  public Comparable parent (Comparable x) {        //Returns the parent of x
    if(root==null) return null;  //If there is no tree
    if(root.item.compareTo(x)==0) return null;  //If x is the root
    Node p = root;
    while(p!=null) {
      if(p.left!=null && p.right!=null) {
        if(p.left.item.compareTo(x)==0 || p.right.item.compareTo(x)==0) return p.item;
        else if (x.compareTo(p.item)>0) p = p.right;      //x is greater than p
        else p = p.left;
      }
      else if(p.left!=null && p.right==null) {
        if(p.left.item.compareTo(x)==0) return p.item;
        else p = p.left;
      }
      else if(p.left==null && p.right!=null) {
        if(p.right.item.compareTo(x)==0) return p.item;
        else p = p.right;
      }
      else {   //p.left and p.right are null
        return null;
      }
   }
   return null;
  }
 
        

  public Comparable predecessor (Comparable x) {   //Returns the predecessor of x
    Node lastRight = null;
    if(root==null) return null;
    Node p = root;
    while(p!=null) {
      if(p.left!=null && p.right!=null) {
        if(p.item.compareTo(x)==0) {
          p = p.left;
          while(p.right!=null) {
            p = p.right;
          }
          return p.item;
        }
        else if(x.compareTo(p.item)>0) {
           lastRight = p;
           p = p.right;
        }
         
        else p = p.left;
      }
      else if(p.left!=null && p.right==null) {
        if(p.item.compareTo(x)==0) {
          p = p.left;
          while(p.right!=null) {
            p = p.right;
          }
          return p.item;
        }
        else p = p.left;
      }
      else if(p.left==null && p.right!=null) {
        if(p.item.compareTo(x)==0) {
           if(lastRight==null) return null;
           else return lastRight.item; //predecessor is last RIGHT turn getting here
        }   
        else {
          lastRight = p;
          p = p.right;
        }
      }
      else {  //right and left are null
        if(x.compareTo(p.item)==0) {
          if(lastRight==null) return null;
          else return lastRight.item;
          }
          else return null;
      }
    }
    return null;
  }
             

  public Comparable successor (Comparable x) {     //Returns the successor of x
    Node lastLeft = null;
    if(root==null) return null;
    Node p = root;
    while(p!=null) {
      if(p.left!=null && p.right!=null) {
        if(x.compareTo(p.item)==0) {
          p = p.right;
          while(p.left!=null) {
            p = p.left;
          }
          return p.item;
        }
        else if(x.compareTo(p.item)<0){
          lastLeft = p;
          p = p.left;
        }
        else p = p.right;
      }
      else if(p.left!=null && p.right==null) {
        if(x.compareTo(p.item)==0) {  //successor is last LEFT turn getting here
          if(lastLeft==null) return null;
          else return lastLeft.item;
        }
        else {
          lastLeft = p;
          p = p.left;
        }
      }
      else if(p.left==null && p.right!=null) {
        if(x.compareTo(p.item)==0) {
          p = p.right;
          while(p.left!=null) {
            p = p.left;
          }
          return p.item;
        }
        else p = p.right;
      }
      else {
        if(x.compareTo(p.item)==0) {
          if (lastLeft==null) return null;
          else return lastLeft.item;
        }
        else return null;
      }
    }  
    return null;
  }



}
