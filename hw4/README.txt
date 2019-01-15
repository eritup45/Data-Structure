Readme file should include your name, class ID, a brief description of the
code, and other issues students think that will be helpful for the TAs to
understand their homework

406410027, 洪晟瑞

Use a struct bst to store data in a binary search tree.
typedef struct bst{
    int data;
    struct bst *l;
    struct bst *r;
}bst;

(1)Implement a Binary Search Tree with linked lists 
	function:
		(a) bst *insert(bst *tree, int num):
			Insert a number in the tree, and return tree.
		(b) bst *delete_a_node(bst *tree):
			Delete exactly the node "tree".
		(c) bst *bst_delete(bst *tree, int num):
			Delete the num if it exists.
		(d) void bst_search(bst *tree, int num):
			If num exists, set the global variable search_flag to 1.
		(e) void inorder(bst *tree):
			Print out in in order.
		(f) void level_order(bst *tree):
			Print out in level order.
		
(2)Treasure Hunter 
	function:
		(a) int is_contain_bomb(bst *tree, int bomb):
			If there is a word in tree->data containing bomb, return 1, 
			else return 0.
		(b) bst *hunter_delete_a_node(bst *tree):
			Delete exactly the node "tree".
		(c) bst *hunter_delete_bomb(bst *tree, int bomb):
			Delete every data, if containing a word "bomb".
		(d) void print_hunter_least_path(bst *tree, int key, int
			trea_location):
			Print out the path. First, go for key. Second, go for treasure.
			
			

