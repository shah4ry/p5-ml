#include "BinarySearchTree.hpp"
#include "unit_test_framework.hpp"

//empty_impl
//size_impl
//height_impl
//copy_nodes_impl
//destroy_nodes_impl
//find_impl
//insert_impl
//min_element_impl
//max_element_impl
//check_sorting_invariant_impl
//traverse_inorder_impl
//traverse_preorder_impl
//min_greater_than_impl

TEST(test_empty_tree) 
{
    BinarySearchTree<int> bst;
    ASSERT_TRUE(bst.empty());
    ASSERT_EQUAL(bst.size(), 0);
    ASSERT_EQUAL(bst.height(), 0);
    ASSERT_TRUE(bst.check_sorting_invariant());

    BinarySearchTree<int>::Iterator it;
    ASSERT_EQUAL(bst.find(0), it);
    ASSERT_EQUAL(bst.min_element(), it);
    ASSERT_EQUAL(bst.max_element(), it);
    ASSERT_EQUAL(bst.min_greater_than(0), it);

    std::string correct1 = "";
    std::ostringstream os1;
    bst.traverse_inorder(os1);
    ASSERT_EQUAL(correct1, os1.str());

    std::string correct2 = "";
    std::ostringstream os2;
    bst.traverse_preorder(os2);
    ASSERT_EQUAL(correct1, os2.str());
}

TEST(test_single_node)
{
    BinarySearchTree<int> bst1;
    BinarySearchTree<int>::Iterator it = bst1.insert(1);
    BinarySearchTree<int>::Iterator empty_it;
    
    ASSERT_FALSE(bst1.empty());
    ASSERT_EQUAL(bst1.size(), 1);
    ASSERT_EQUAL(bst1.height(), 1);
    ASSERT_TRUE(bst1.check_sorting_invariant());
    ASSERT_EQUAL(bst1.find(1), it);
    ASSERT_EQUAL(bst1.find(0), empty_it);
    ASSERT_EQUAL(bst1.min_element(), it);
    ASSERT_EQUAL(bst1.max_element(), it);
    ASSERT_EQUAL(bst1.min_greater_than(0), it);
    ASSERT_EQUAL(bst1.min_greater_than(1), empty_it);

    BinarySearchTree<int> bst2;
    bst2.insert(100);
    bst2 = bst1;
    
    ASSERT_FALSE(bst2.empty());
    ASSERT_EQUAL(bst2.size(), bst1.size());
    ASSERT_EQUAL(bst2.height(), bst1.height());
    ASSERT_TRUE(bst2.check_sorting_invariant());
    ASSERT_EQUAL(*bst2.find(1), *bst1.find(1));
    ASSERT_EQUAL(bst2.find(0), bst1.find(0));
    ASSERT_EQUAL(*bst2.min_element(), *bst1.min_element());
    ASSERT_EQUAL(*bst2.max_element(), *bst1.min_element());
    ASSERT_EQUAL(*bst2.min_greater_than(0), *bst1.min_greater_than(0));
    ASSERT_EQUAL(bst2.min_greater_than(1), bst1.min_greater_than(1));

    std::string correct1 = "1 ";
    std::ostringstream os1;
    bst2.traverse_inorder(os1);
    ASSERT_EQUAL(correct1, os1.str());

    std::string correct2 = "1 ";
    std::ostringstream os2;
    bst2.traverse_preorder(os2);
    ASSERT_EQUAL(correct1, os2.str());
}

TEST(test_seven_nodes)
{
    BinarySearchTree<int> bst;
    BinarySearchTree<int>::Iterator empty_it;

    bst.insert(10);
    ASSERT_TRUE(bst.check_sorting_invariant());
    bst.insert(30);
    ASSERT_TRUE(bst.check_sorting_invariant());
    bst.insert(20);
    ASSERT_TRUE(bst.check_sorting_invariant());
    bst.insert(40);
    ASSERT_TRUE(bst.check_sorting_invariant());
    bst.insert(21);
    ASSERT_TRUE(bst.check_sorting_invariant());
    bst.insert(22);
    ASSERT_TRUE(bst.check_sorting_invariant());
    bst.insert(39);
    ASSERT_TRUE(bst.check_sorting_invariant());

    ASSERT_FALSE(bst.empty());
    ASSERT_EQUAL(bst.size(), 7);
    ASSERT_EQUAL(bst.height(), 5);
    ASSERT_EQUAL(*bst.find(20), 20);
    ASSERT_EQUAL(*bst.min_element(), 10);
    ASSERT_EQUAL(*bst.max_element(), 40);
    ASSERT_EQUAL(*bst.min_greater_than(5), 10);
    ASSERT_EQUAL(*bst.min_greater_than(20), 21);
    ASSERT_EQUAL(*bst.min_greater_than(25), 30);
    ASSERT_EQUAL(bst.min_greater_than(40), empty_it);
    ASSERT_EQUAL(bst.min_greater_than(45), empty_it);

    std::string correct1 = "10 20 21 22 30 39 40 ";
    std::ostringstream os1;
    bst.traverse_inorder(os1);
    ASSERT_EQUAL(correct1, os1.str());

    std::string correct2 = "10 30 20 21 22 40 39 ";
    std::ostringstream os2;
    bst.traverse_preorder(os2);
    ASSERT_EQUAL(correct2, os2.str());
}

TEST(test_balanced_tree)
{
    BinarySearchTree<int> bst;
    BinarySearchTree<int>::Iterator empty_it;
    bst.insert(40);
    ASSERT_TRUE(bst.check_sorting_invariant());
    bst.insert(20);
    ASSERT_TRUE(bst.check_sorting_invariant());
    bst.insert(60);
    ASSERT_TRUE(bst.check_sorting_invariant());
    bst.insert(70);
    ASSERT_TRUE(bst.check_sorting_invariant());
    bst.insert(50);
    ASSERT_TRUE(bst.check_sorting_invariant());
    bst.insert(10);
    ASSERT_TRUE(bst.check_sorting_invariant());
    bst.insert(30);
    ASSERT_TRUE(bst.check_sorting_invariant());
    
    ASSERT_FALSE(bst.empty());
    ASSERT_EQUAL(bst.size(), 7);
    ASSERT_EQUAL(bst.height(), 3);
    ASSERT_EQUAL(*bst.min_element(), 10);
    ASSERT_EQUAL(*bst.max_element(), 70);
    ASSERT_EQUAL(*bst.min_greater_than(0), 10);
    ASSERT_EQUAL(*bst.min_greater_than(30), 40);
    ASSERT_EQUAL(bst.min_greater_than(70), empty_it);

    BinarySearchTree<int>::Iterator it = bst.find(10);
    std::ostringstream os1;
    for(; it != bst.end(); it++)
    {
        os1 << *it << " ";
    }
    ASSERT_EQUAL(os1.str(), "10 20 30 40 50 60 70 ");

    *bst.find(30) = 35;
    it = bst.find(10);
    std::ostringstream os2;
    for(; it != bst.end(); it++)
    {
        os2 << *it << " ";
    }
    ASSERT_EQUAL(os2.str(), "10 20 35 40 50 60 70 ");
}

TEST(test_op_in_argument)
{
    BinarySearchTree<int> bst;
    bst.insert(1);
    bst.insert(3);
    bst.insert(4);
    bst.insert(2);
    ASSERT_EQUAL(*bst.begin(), 1);
    ASSERT_EQUAL(*++bst.begin(), 2);
    ASSERT_EQUAL(*++++bst.begin(), 3);
    ASSERT_EQUAL(*++++++bst.begin(), 4);
    ASSERT_EQUAL(bst.size(), 4);
}

TEST(test_large)
{
    BinarySearchTree<int> bst;

    //insert even
    for(int i = 0; i < 100; i++)
    {
        ASSERT_EQUAL(*bst.insert(2 * i), 2 * i);
    }
    ASSERT_EQUAL(bst.size(), 100);
    ASSERT_EQUAL(bst.height(), 100);
    ASSERT_EQUAL(*bst.max_element(), 198)

    //insert odd
    for(int i = 0; i < 100; i++)
    {
        ASSERT_EQUAL(*bst.insert(2 * i + 1), 2 * i + 1);
    }
    ASSERT_EQUAL(bst.size(), 200);
    ASSERT_EQUAL(bst.height(), 101);
    ASSERT_EQUAL(*bst.max_element(), 199)
}

TEST(test_list_as_tree_right)
{
    BinarySearchTree<int> bst;
    ASSERT_TRUE(bst.check_sorting_invariant());

    bst.insert(1);
    ASSERT_EQUAL(*bst.max_element(), 1);
    ASSERT_TRUE(bst.check_sorting_invariant());

    bst.insert(2);
    ASSERT_EQUAL(*bst.max_element(), 2);
    ASSERT_TRUE(bst.check_sorting_invariant());

    bst.insert(3);
    ASSERT_EQUAL(*bst.max_element(), 3);
    ASSERT_TRUE(bst.check_sorting_invariant());

    bst.insert(4);
    ASSERT_EQUAL(*bst.max_element(), 4);
    ASSERT_TRUE(bst.check_sorting_invariant());

    ASSERT_FALSE(bst.empty());
    ASSERT_EQUAL(bst.size(), 4);
    ASSERT_EQUAL(bst.height(), 4);
    ASSERT_EQUAL(*bst.min_element(), 1);
    ASSERT_EQUAL(*bst.max_element(), 4);
    ASSERT_EQUAL(*bst.min_greater_than(2), 3);

    std::string correct1 = "1 2 3 4 ";
    std::ostringstream os1;
    bst.traverse_inorder(os1);
    ASSERT_EQUAL(correct1, os1.str());

    std::string correct2 = "1 2 3 4 ";
    std::ostringstream os2;
    bst.traverse_preorder(os2);
    ASSERT_EQUAL(correct2, os2.str());
}

TEST(test_list_as_tree_left)
{
    BinarySearchTree<int> bst;
    ASSERT_TRUE(bst.check_sorting_invariant());

    bst.insert(4);
    ASSERT_EQUAL(*bst.min_element(), 4);
    ASSERT_TRUE(bst.check_sorting_invariant());

    bst.insert(3);
    ASSERT_EQUAL(*bst.min_element(), 3);
    ASSERT_TRUE(bst.check_sorting_invariant());

    bst.insert(2);
    ASSERT_EQUAL(*bst.min_element(), 2);
    ASSERT_TRUE(bst.check_sorting_invariant());

    bst.insert(1);
    ASSERT_EQUAL(*bst.min_element(), 1);
    ASSERT_TRUE(bst.check_sorting_invariant());

    ASSERT_FALSE(bst.empty());
    ASSERT_EQUAL(bst.size(), 4);
    ASSERT_EQUAL(bst.height(), 4);
    ASSERT_EQUAL(*bst.min_element(), 1);
    ASSERT_EQUAL(*bst.max_element(), 4);
    ASSERT_EQUAL(*bst.min_greater_than(2), 3);

    std::string correct1 = "1 2 3 4 ";
    std::ostringstream os1;
    bst.traverse_inorder(os1);
    ASSERT_EQUAL(correct1, os1.str());

    std::string correct2 = "4 3 2 1 ";
    std::ostringstream os2;
    bst.traverse_preorder(os2);
    ASSERT_EQUAL(correct2, os2.str());
}

TEST_MAIN()
