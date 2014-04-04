#ifndef LAB3_TESTS_HPP
#define LAB3_TESTS_HPP

#define ASSERT_TRUE(T) if (!(T)) return false;
#define ASSERT_FALSE(T) if ((T)) return false;

//#include "PriorityQueue.hpp"
#include "BinarySearchTree.hpp"

// Libraries needed for BinarySearchTreeTest
#include <sstream>
#include <queue>

/*class PriorityQueueTest
{
public:
  bool test1()
  {
    PriorityQueue q(16);
    ASSERT_TRUE( q.empty() );
    ASSERT_TRUE( !q.full() );
    ASSERT_TRUE( q.size() == 0 );
    return true;
  }

  bool test2()
  {
    PriorityQueue q(2);
    ASSERT_TRUE( q.enqueue(10) );
    ASSERT_TRUE( !q.empty() );
    ASSERT_TRUE( !q.full() );
    ASSERT_TRUE( q.size() == 1 );
    ASSERT_TRUE( q.max() == 10 );

    ASSERT_TRUE( q.dequeue() );
    ASSERT_TRUE( q.empty() );
    ASSERT_TRUE( !q.full() );
    ASSERT_TRUE( q.size() == 0 );
    return true;
  }

  bool test3()
  {
    PriorityQueue q(3);
    ASSERT_TRUE( q.enqueue(5) );
    ASSERT_TRUE( q.max() == 5 );
    ASSERT_TRUE( q.enqueue(3) );
    ASSERT_TRUE( q.max() == 5 );
    ASSERT_TRUE( q.enqueue(4) );
    ASSERT_TRUE( q.max() == 5 );
    ASSERT_TRUE( q.full() );

    ASSERT_TRUE( !q.enqueue(7) );
    ASSERT_TRUE( q.max() == 5 );
    ASSERT_TRUE( q.full() );
    return true;
  }
};
*/
class BinarySearchTreeTest
{
private:
  // Traverse the tree in level-order so we can check if it was constructed
  // properly. Output is as follows:
  //   "val1 val2 ... valN"
  // where vali is the value of node i, using level-order traversal.
  std::string BinarySearchTreeTest::level_order(BinarySearchTree::Node* root)
  {
    // If no nodes, return an empty string.
    if (root == NULL) {
      return "";
    }
    
    std::stringstream ss;
    std::queue<BinarySearchTree::Node*> node_queue;
    node_queue.push(root);
    while (!node_queue.empty()) {
      BinarySearchTree::Node* cur_node = node_queue.front();
      node_queue.pop();
      ss << cur_node->val << " ";
      if (cur_node->left != NULL) {
        node_queue.push(cur_node->left);
      }
      if (cur_node->right != NULL) {
        node_queue.push(cur_node->right);
      }
    }
    
    std::string level_order_str = ss.str();
    // There is a trailing space at the end of the string; return everything
    // before this.
    return level_order_str.substr(0, level_order_str.size() - 1);
  }

public:
  bool test1()
  {
    // We expect an empty tree at construction.
    std::string expected_tree_level_order = "";
    
    BinarySearchTree bst;
    ASSERT_TRUE(bst.root_ == NULL);
    ASSERT_TRUE(bst.size_ == 0 && bst.size() == 0);
    
    std::string tree_level_order = level_order(bst.root_);
    // Compare the tree's representation to the expected tree.
    ASSERT_TRUE(tree_level_order.compare(expected_tree_level_order) == 0)
    return true;
  }

  bool test2()
  {
    // We expect a single root node with value "5" after everything.
    std::string expected_tree_level_order = "5";
    
    BinarySearchTree bst;
    ASSERT_TRUE(bst.insert(5));
    ASSERT_TRUE(!bst.remove(4));
    ASSERT_TRUE(bst.exists(5));
    ASSERT_TRUE(bst.max() == bst.min() && bst.max() == 5);
    ASSERT_TRUE(bst.size() == 1);
    
    std::string tree_level_order = level_order(bst.root_);
    // Compare the tree's representation to the expected tree.
    ASSERT_TRUE(tree_level_order.compare(expected_tree_level_order) == 0)
    return true;
  }

  bool test3()
  {
    // We expect a 2-node tree at the end of this function -- root node 10 and
    // a child node with value 6.
    std::string expected_tree_level_order = "10 6";
    
    BinarySearchTree bst;
    ASSERT_TRUE(bst.insert(10));
    ASSERT_TRUE(bst.insert(8));
    ASSERT_TRUE(bst.size() == 2);
    ASSERT_TRUE(bst.insert(6));
    ASSERT_TRUE(bst.size() == 3);

    ASSERT_TRUE(bst.remove(8));
    ASSERT_TRUE(bst.size() == 2);
    
    std::string tree_level_order = level_order(bst.root_);
    // Compare the tree's representation to the expected tree.
    ASSERT_TRUE(tree_level_order.compare(expected_tree_level_order) == 0)
    return true;
  }bool test4()
{

if (1) {
    cout<<"\n\nRunning depth test ...          ";
    BinarySearchTree bst; 
    bst.insert(20);
    ASSERT_TRUE(bst.depth()==0);
    bst.insert(10);
    bst.insert(30);
    ASSERT_TRUE(bst.depth()==1);
    bst.insert(5);
    bst.insert(100);
    ASSERT_TRUE(bst.depth()==2);
    bst.insert(999);
    ASSERT_TRUE(bst.depth()==3);
    cout<<"[Pass]\n";
   }


//Test WF_Tree_1
if (1) //Test constructor/destructor and default values
{
 	cout << "Running test WF_Tree_1" << endl;
 	BinarySearchTree* test= new BinarySearchTree;
 	ASSERT_TRUE((*test).size() == 0)
 	
 	for (int i = 0; i < 1000; i++)
 	{
     	ASSERT_TRUE((*test).exists(i) == 0)
     	ASSERT_TRUE((*test).remove(i) == 0)
 	}
 	delete test;   	
}

//Test WF_Tree_2
if (1) //Test Single Insert/remove
{
 	cout << "Running test WF_Tree_2" << endl;
 	BinarySearchTree test;
 	ASSERT_TRUE(test.size() ==0)
 	
 	ASSERT_TRUE(test.insert(5))
 	ASSERT_TRUE(test.size()== 1)
 	ASSERT_TRUE(test.depth() == 0)
 	ASSERT_TRUE(test.remove(5))
 	ASSERT_FALSE(test.remove(5))
 	ASSERT_TRUE(test.size() == 0)
 	ASSERT_TRUE(test.exists(5) == 0)
}
//Test WF_Tree_3
if (1) //Test remove on root with single child; no sub-children
{
 	cout << "Running test WF_Tree_3" << endl;
 	BinarySearchTree test_l;
 	BinarySearchTree test_r;
 	
 	ASSERT_TRUE(test_l.insert(10))
 	ASSERT_TRUE(test_r.insert(10))
 	
 	ASSERT_TRUE(test_l.insert(5))
 	ASSERT_TRUE(test_r.insert(15))
 	ASSERT_TRUE(test_l.depth() == test_r.depth() && test_l.depth() == 1)
 	ASSERT_TRUE(test_l.size() == test_r.size() && test_l.size() == 2)
 	
 	ASSERT_TRUE(test_l.remove(10))
 	ASSERT_TRUE(test_r.remove(10)) 
}/*
//Test WF_Tree_4
if (1) //Test remove on root with single child; 2 sub-children
{
 	cout << "Running test WF_Tree_4" << endl;
 	BinarySearchTree test_l;
 	BinarySearchTree test_r;
 	
 	ASSERT_TRUE(test_l.insert(10))
 	ASSERT_TRUE(test_r.insert(10))
 	
 	ASSERT_TRUE(test_l.insert(5))
 	ASSERT_TRUE(test_r.insert(15))
 	
 	ASSERT_TRUE(test_l.insert(2))
 	ASSERT_TRUE(test_r.insert(13))
 	
 	ASSERT_TRUE(test_l.insert(7))
 	ASSERT_TRUE(test_r.insert(16))
 	
 	ASSERT_TRUE(test_l.size() == 4)
 	ASSERT_TRUE(test_l.depth() == 2)
 	ASSERT_TRUE(test_r.size() == 4)
 	ASSERT_TRUE(test_r.depth() == 2)
 	
 	ASSERT_TRUE(test_l.remove(10))
 	ASSERT_TRUE(test_r.remove(10))
 	
 	ASSERT_TRUE(test_l.size() == 3)
 	ASSERT_TRUE(test_l.depth() == 1)
 	ASSERT_TRUE(test_r.size() == 3)
 	ASSERT_TRUE(test_r.depth() == 1)
	// test_l.print(); //Expected In-order: 2, 5, 7
 	//test_r.print(); //Expected In-order: 13, 15, 16 
}
*/
//Test WF_Tree_5
if (1) //Test remove on root with 2 children; no sub-children
{
 	cout << "Running test WF_Tree_5" << endl;
 	BinarySearchTree test;
 	
 	ASSERT_TRUE(test.insert(10))
 	ASSERT_TRUE(test.insert(5))
 	ASSERT_TRUE(test.insert(15))
 	
 	ASSERT_TRUE(test.size() == 3)
 	ASSERT_TRUE(test.depth() == 1)
 	
 	ASSERT_TRUE(test.remove(10))
 	ASSERT_TRUE(test.size() == 2)
 	ASSERT_TRUE(test.depth() == 1)
 	//test.print(); //Expected in-order: 5, 15
}

//Test WF_Tree_6
if (1) //Test remove on root with 2 children; 2 full sub-trees
{
 	cout << "Running test WF_Tree_6" << endl;
 	BinarySearchTree test;
 	
 	ASSERT_TRUE(test.insert(10))
 	ASSERT_TRUE(test.insert(5))
 	ASSERT_TRUE(test.insert(15))
 	
 	ASSERT_TRUE(test.insert(4))
 	ASSERT_TRUE(test.insert(6))
 	
 	ASSERT_TRUE(test.insert(14))
 	ASSERT_TRUE(test.insert(16))
 	ASSERT_TRUE(test.size() == 7)
 	ASSERT_TRUE(test.depth() == 2)
 	
	// test.print(); //Expected in-order: 4, 5, 6, 10, 14, 15, 16
 	
 	ASSERT_TRUE(test.remove(10))
 	ASSERT_TRUE(test.size() == 6)
 	ASSERT_TRUE(test.depth() == 2)
 	//test.print(); //Expected in-order: 5, 15 // ???
}

//Test WF_Tree_7
if (1) //Test remove on non-root leaves
{
 	cout << "Running test WF_Tree_7" << endl;
 	BinarySearchTree test;
 	
 	ASSERT_TRUE(test.insert(10))
 	ASSERT_TRUE(test.insert(5))
 	ASSERT_TRUE(test.insert(15))
 	
 	ASSERT_TRUE(test.insert(4))
 	ASSERT_TRUE(test.insert(6))
 	
 	ASSERT_TRUE(test.insert(14))
 	ASSERT_TRUE(test.insert(16))
 	
 	ASSERT_TRUE(test.size() == 7)
 	ASSERT_TRUE(test.depth() == 2)
 	
 	ASSERT_TRUE(test.remove(4))
 	ASSERT_TRUE(test.remove(6))
 	ASSERT_TRUE(test.remove(14))
 	ASSERT_TRUE(test.remove(16))
 	
 	ASSERT_TRUE(test.size() == 3)
 	ASSERT_TRUE(test.depth() == 1)
}
//Test WF_Tree_8
if (1) //Test remove on nodes with 1 child
{
 	cout << "Running test WF_Tree_8" << endl;
 	BinarySearchTree test;
 	
 	ASSERT_TRUE(test.insert(10))
 	ASSERT_TRUE(test.insert(5))
 	ASSERT_TRUE(test.insert(15))
 	ASSERT_TRUE(test.insert(3))  //Left Child
 	ASSERT_TRUE(test.insert(25)) //Right Child
 	
 	ASSERT_TRUE(test.size() == 5)
 	ASSERT_TRUE(test.depth() == 2)
 	
 	ASSERT_TRUE(test.remove(5))
 	ASSERT_TRUE(test.remove(15))
// 	test.print(); //Expected in-order 3, 10, 25
 	
 	ASSERT_TRUE(test.size() == 3)
 	ASSERT_TRUE(test.depth() == 1)
}
//Test WF_Tree_9
if (1) //Test remove on nodes with 2 children
{
 	cout << "Running test WF_Tree_9" << endl;
 	BinarySearchTree test;
 	
 	ASSERT_TRUE(test.insert(10))
 	ASSERT_TRUE(test.insert(5))
 	ASSERT_TRUE(test.insert(15))
 	ASSERT_TRUE(test.insert(3))
 	ASSERT_TRUE(test.insert(6))
 	ASSERT_TRUE(test.insert(25))
 	ASSERT_TRUE(test.insert(11))
 	
 	ASSERT_TRUE(test.size() == 7)
 	ASSERT_TRUE(test.depth() == 2)
 	
 	ASSERT_TRUE(test.remove(5))
 	ASSERT_TRUE(test.remove(15))
// 	test.print(); //Expected in-order 3, 6, 10, 11, 25
// order may vary depending on the implementation (max in left vs min in right)
 	
 	ASSERT_TRUE(test.size() == 5)
 	ASSERT_TRUE(test.depth() == 2) 
}

//Test WF_TREE_10
if (1) //Test many ordered inserts/deletes
{
 	cout << "Running test WF_TREE_10" << endl;
 	BinarySearchTree test;
 	
 	for (int i = 0; i <= 1000; i++)
 	{
      	ASSERT_TRUE(test.insert(i))
      	ASSERT_TRUE(test.exists(i))
      	ASSERT_TRUE(test.size() == i + 1)
      	ASSERT_TRUE(test.depth() == i)
      	ASSERT_TRUE(test.max() == i)
      	ASSERT_TRUE(test.min() == 0)
 	}
 	for (int i = 1000; i >= 1; i--)
 	{
      	ASSERT_TRUE(test.remove(i))
      	ASSERT_FALSE(test.remove(i))
      	ASSERT_FALSE(test.exists(i))
      	ASSERT_TRUE(test.size() == i)
      	if ( i != 0) ASSERT_TRUE(test.depth() == i -1)
      	if (i != 0) ASSERT_TRUE(test.max() == i - 1)
      	if (i != 0) ASSERT_TRUE(test.min() == 0)
 	}	
}
//Test WF_TREE_11
if (1) //Test random inserts/deletes
{
	cout << "Running Test WF_TREE_11" << endl;
	BinarySearchTree test;
	
	bool done = false;
	int num = 10000;
	int stored[num];
	int x;
	int counter = 0;
	
	while (!done)
	{
      	do
      	{
             	x = rand() % 10000;
      	} while (test.exists(x) == true);
      	ASSERT_TRUE(test.insert(x))
      	stored[counter] = x;
      	counter++;
      	if (counter == num) done = true;
	}
	while (test.size() != 0)
	{
      	int target = stored[rand() % num];
     	// cout << "Target: " << target << "; " << test.exists(target) << endl;
    	if (test.exists(target)) ASSERT_TRUE(test.remove(target))  	
	}
} //WHOEVER REMOVED THIS BRACKET IS PURE EVIL

// Test WF_Tree_12
if (1) // Test tree is proper size
{
cout << "Running Test WF_Tree_12" << endl;
 for (int i = 0; i <= 5; i++)
 {
  	BinarySearchTree test;
  	int x = rand() % 300;
  	
  	for (int j = 0; j <= x; j++)
  	{
       	ASSERT_TRUE(test.insert(j))
       	ASSERT_TRUE(test.size() == j + 1)	
  	}
  	ASSERT_TRUE( test.size() == x + 1)
  	
  	for (int j = x; j >= 0; j--)
  	{
       	ASSERT_TRUE(test.remove(j))
       	ASSERT_TRUE(test.size() == j)	
  	}
  	ASSERT_TRUE( test.size() == 0)
 }  	
   	
}

//Test WF_Tree_13
if(1) // Test max/min functions as tree is filled
{
 	BinarySearchTree test;
 	test.insert(10);
 	ASSERT_TRUE(test.min() == 10)
 	ASSERT_TRUE(test.max() == 10)
 	int curmax = 10;
 	int curmin = 10;
 	
 	for (int i = 0; i <= 10000; i++)
 	{
      	int x = rand() % 2000 - 1000; //Numbers range from -1000 to 1000
      	
      	if (!test.exists(x))
      	{
           	if (x > curmax) curmax = x;
           	if (x < curmin) curmin = x;
           	ASSERT_TRUE(test.insert(x))
           	ASSERT_TRUE(test.max() == curmax)
           	ASSERT_TRUE(test.min() == curmin)
      	}
     	
 	}  	
}

//Test WF_Tree_14
if (1) // Test depth in hard-coded cases
{
 	BinarySearchTree a, b, c, d, e;
 	int num[5][5] = {{1, 2, 3, 4, 5},
                  	{5, 4, 3, 2, 1},
                  	{5, 4, 6, 3, 7},
                  	{5, 10, 9, 8, 7},
                  	{5, 10, 11, 8, 7}
                  	};
  
 	for (int i = 0; i < 5; i++)
     	a.insert(num[0][i]);
     	ASSERT_TRUE(a.depth() == 4)
     	
 	for (int i = 0; i < 5; i++)
     	b.insert(num[1][i]);
     	ASSERT_TRUE(b.depth() == 4)
     	
 	for (int i = 0; i < 5; i++)
     	c.insert(num[2][i]);
     	ASSERT_TRUE(c.depth() == 2)
     	
 	for (int i = 0; i < 5; i++)
     	d.insert(num[3][i]);
     	ASSERT_TRUE(d.depth() == 4)
     	
 	for (int i = 0; i < 5; i++)
     	e.insert(num[4][i]);
     	ASSERT_TRUE(e.depth() == 3)
}


return true;
}
};


#endif
