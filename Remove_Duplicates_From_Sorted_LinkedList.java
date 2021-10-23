/**
 * Definition for singly-linked list.
 * public class ListNode {
 *     int val;
 *     ListNode next;
 *     ListNode() {}
 *     ListNode(int val) { this.val = val; }
 *     ListNode(int val, ListNode next) { this.val = val; this.next = next; }
 * }
 */
public class Remove_Duplicates_From_Sorted_LinkedList {
    public ListNode deleteDuplicates(ListNode head) {
        
        
      //Initializing first and second nodes
       ListNode first = head;
        
        ListNode second = head;
        
        //Terminating condition
        while(first!=null && second !=null){
            
            //Checking if the nodes are same
            while(second!=null && first.val == second.val){
                second= second.next;
            }
            
           
            //Moving to the next node
            first.next = second;
            first=second;
            
            
            if(second!=null)
            second = second.next;
            
            
        }
        //Returning the head node of the updated list
        return head;
        
    }
}

//Time complexity: O(n)
