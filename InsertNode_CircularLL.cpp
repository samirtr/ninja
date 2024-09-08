Problem statement
You are given a circular singly linked list, where every node in the linked list contains a pointer 'next' which points to the next node in the list, and the last node points to the head of the list.



All nodes have some positive integer value 'data' associated with them.



Your task is to insert a new node with 'data' equal to 'val' in the linked list at a given position 'k'.



Note:

The position given will always be less than or equal to the length of the linked list. Assume all the indexing starts from '0'.


Example:
Input : 'k' = 1, 'val' = 5, 'list' = [1, 2, 3, 4]

Output: 1 5 2 3 4

Explanation:
The node with 'data' = 5, is inserted at position 1(0 indexed) in the circular linked list as follows:




Detailed explanation ( Input/output format, Notes, Images )
Sample Input 1:
4 0 5
1 2 3 4


Sample Output 1:
5 1 2 3 4


Explanation Of Sample Input 1 :
In this case, ‘k’ = 0 denotes the starting index of the list, so the new element is inserted before the head of the list and the new head will be then a node with ‘data’ = 5.

Hence, the resulting circular linked list would be : 5 1 2 3 4


Sample Input 2 :
3 2 4
10 11 5


Sample Output 2 :
10 11 4 5


Expected Time Complexity:
Try to do this in O(k).


Constraints :
1 <= n <= 10^4
0 <= k <= n
1 <= val <= 10^5
1 <= Node.data <= 10^5

Time Limit: 1 sec

Solution:
/*
 * Definition for linked list.
 * class Node {
 *  public:
 *		int data;
 *		Node *next;
 *		Node() : data(0), next(nullptr){};
 *		Node(int x) : data(x), next(nullptr){};
 *		Node(int x, Node *next) : data(x), next(next){};
 * };
 */

Node* insert(int k, int val, Node *head) {
	// Write Your Code Here.

	Node* temp1 = new Node(val);
	if(k==0){
		Node* temp = head;
		while(temp->next!=head) {
			temp=temp->next;
		}
		temp->next=temp1;
		temp1->next=head;
		return temp1;
	}
    Node* cur = head;
	for(int i=0;i<k-1;i++){
		cur=cur->next;
	}	
	temp1->next=cur->next;
	cur->next=temp1;
	return head;
}


