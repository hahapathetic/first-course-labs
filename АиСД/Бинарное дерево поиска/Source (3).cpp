#include "BinarySearchTree.h"
#include <iostream>

void testTree()
{
    std::cout << "-----------Тесты insert, getCount, getHeight, iterativeSearch, deleteKey, print-----------\n";
    BinarySearchTree<int> tree;
    tree.insert(15);
    tree.insert(10);
    tree.insert(7);
    tree.insert(11);
    if (tree.insert(13))
    {
        std::cout << "inserted\n";
    }
    if (!tree.insert(13))
    {
        std::cout << "already exists\n";
    }
    tree.insert(8);
    tree.insert(5);
    tree.insert(25);
    tree.insert(21);
    tree.insert(27);
    tree.insert(30);
    tree.insert(18);
    tree.insert(23);

    tree.print(std::cout);
    std::cout << '\n';
    std::cout << "count: " << tree.getCount() << '\n';
    std::cout << "height: " << tree.getHeight() << '\n';

    tree.insert(35);

    tree.print(std::cout);
    std::cout << '\n';
    std::cout << "count: " << tree.getCount() << '\n';
    std::cout << "height: " << tree.getHeight() << '\n';

    if (!tree.iterativeSearch(100))
    {
        std::cout << "not found\n";
    }
    if (!tree.iterativeSearch(1))
    {
        std::cout << "not found\n";
    }
    if (tree.iterativeSearch(10))
    {
        std::cout << "found\n";
    }
    if (tree.iterativeSearch(35))
    {
        std::cout << "found\n";
    }
    if (tree.iterativeSearch(15))
    {
        std::cout << "found\n";
    }

    if (tree.deleteKey(15))
    {
        std::cout << "deleted\n";
    }
    tree.print(std::cout);
    std::cout << '\n';
    if (!tree.deleteKey(100))
    {
        std::cout << "not found\n";
    }

    if (tree.deleteKey(18))
    {
        std::cout << "deleted\n";
    }
    tree.print(std::cout);
    std::cout << '\n';

    if (tree.deleteKey(10))
    {
        std::cout << "deleted\n";
    }
    tree.print(std::cout);
    std::cout << '\n';

   
    tree.print(std::cout);
    std::cout << '\n';
}

void testTreeAdvanced()
{
    std::cout << "-----------Тесты inorderWalk, iterativeInorderWalk, walkByLevels, isSimilar, isIdenticalKey-----------\n";
    BinarySearchTree<int> firstTree;

    // empty tree
    firstTree.inorderWalk(std::cout); 
    std::cout << '\n';
    firstTree.iterativeInorderWalk(std::cout); 
    std::cout << '\n';
    firstTree.walkByLevels(std::cout); 
    std::cout << '\n';

    firstTree.insert(10);
    firstTree.insert(6);
    firstTree.insert(8);
    firstTree.insert(1);
    firstTree.insert(15);
    firstTree.insert(12);
    firstTree.insert(14);
    firstTree.insert(17);

    BinarySearchTree<int> secondTree;
    secondTree.insert(15);
    secondTree.insert(17);
    secondTree.insert(12);
    secondTree.insert(14);
    secondTree.insert(10);
    secondTree.insert(8);
    secondTree.insert(6);
    secondTree.insert(1);

    firstTree.inorderWalk(std::cout); std::cout << '\n';
    secondTree.iterativeInorderWalk(std::cout); std::cout << '\n';
    firstTree.walkByLevels(std::cout); std::cout << '\n';
    secondTree.walkByLevels(std::cout); std::cout << '\n';
    // true
    std::cout << "similar: " << firstTree.isSimilar(secondTree) << '\n';

    secondTree.deleteKey(17);


    firstTree.inorderWalk(std::cout); std::cout << '\n';
    secondTree.iterativeInorderWalk(std::cout); std::cout << '\n';
    firstTree.walkByLevels(std::cout); std::cout << '\n';
    secondTree.walkByLevels(std::cout); std::cout << '\n';
    // false
    std::cout << "similar: " << firstTree.isSimilar(secondTree) << '\n';

    firstTree.deleteKey(17);

    firstTree.inorderWalk(std::cout); std::cout << '\n';
    secondTree.iterativeInorderWalk(std::cout); std::cout << '\n';
    firstTree.walkByLevels(std::cout); std::cout << '\n';
    secondTree.walkByLevels(std::cout); std::cout << '\n';
    // true
    std::cout << "similar: " << firstTree.isSimilar(secondTree) << '\n';
    secondTree.print(std::cout);  std::cout << '\n';

    firstTree.deleteKey(12);

    firstTree.inorderWalk(std::cout); std::cout << '\n';
    secondTree.iterativeInorderWalk(std::cout); std::cout << '\n';
    firstTree.walkByLevels(std::cout); std::cout << '\n';
    secondTree.walkByLevels(std::cout); std::cout << '\n';
    // false
    std::cout << "similar: " << firstTree.isSimilar(secondTree) << '\n';

    // with empty tree
    std::cout << "similar: " << firstTree.isSimilar(BinarySearchTree<int>()) << '\n';
    std::cout << "similar: " << BinarySearchTree<int>().isSimilar(secondTree) << '\n';

    BinarySearchTree<int> thirdTree;
    thirdTree.insert(9);
    thirdTree.insert(11);
    thirdTree.insert(16);
    thirdTree.insert(13);
    thirdTree.insert(7);
    thirdTree.insert(5);
    thirdTree.insert(4);

    std::cout << "First Tree : \n";
    firstTree.print(std::cout);  std::cout << '\n';
    std::cout << "Third tree: \n";
    thirdTree.print(std::cout);  std::cout << '\n';

    // false
    std::cout << "has same: " << firstTree.isIdenticalKey(thirdTree) << '\n';

    BinarySearchTree<int> fourthTree;
    fourthTree.insert(9);
    fourthTree.insert(11);
    fourthTree.insert(16);
    fourthTree.insert(15);  // !
    fourthTree.insert(7);
    fourthTree.insert(5);
    fourthTree.insert(4);

    std::cout << "Third tree: \n";
    fourthTree.print(std::cout);  std::cout << '\n';

    // true
    std::cout << "has same: " << firstTree.isIdenticalKey(fourthTree) << '\n';

    // with empty tree
    std::cout << "has same: " << firstTree.isIdenticalKey(BinarySearchTree<int>()) << '\n';
    std::cout << "has same: " << BinarySearchTree<int>().isIdenticalKey(secondTree) << '\n';
}

int main()
{
    setlocale(LC_ALL, "ru");
    testTree();
    testTreeAdvanced();

    return 0;
}
