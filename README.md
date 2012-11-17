csci333-AVLtree
===============

For this project, I implemented an AVL tree and focused on the insert and remove methods.  The insert and remove methods have much in common but the remove involved a few extra elements of complexity.  

In the remove method, for simplicity, I always used the IOP rather than alternating between the IOP and IOS in a systematic way.  I also decided in my public print method to include a second left justified printout which displays value, balance pairs in the format [value,balance].  I thought this information would be helpful for evaluation purposes but I can also comment the left justified printing out as I had done for the previous BST lab.

The procedure for the insert was to find the critical node, the last 1 or -1 node on the path to the insert location.  After inserting the new node, the balances of the nodes down from the critical node to the new node were updated appropriately.  If the critical node had a 2 or -2 balance, then rotations were made to bring the AVL tree back into equilibrium.

Instead of calculating the resulting balance changes, it is possible to map the balances of the two or three nodes whose balances change during rotations before the rotations are done.  In implementation, I identified the type of rotation that was going to be done and updated the balances before performing this rotation.  Then I rotated.

During an insert, a single rotation updates two balances and a double rotation updates three balances.  Taking a look at all the possible balance patterns prior to rotation yields the following.  Insert balances that require rotation take the form (2 or -2,1 or -1,0 or 1 or -1).  There are 2*2*3 or 12 possible combinations.  I stored the relevant pre-rotation 2 or 3 balances as a balance vector.

All balances in the form (2,1,x) or (-2,-1,y) become (0,0,x) and (0,0,y) after rotation.
All balances in the form (2 or -2,1 or -1,0) become (0,0,0).  This is restating the above condition but also including (2,-1,0) and (-2,1,0).
(2,-1,1) becomes (-1,0,0) and (2,-1,-1) becomes (0,1,0).
(-2,1,-1) becomes (1,0,0) and (-2,1,1) becomes (0,-1,0).  
This covers all 12 cases.  Notice the symmetry in the balance adjustments.  With less than 5 comparisons, we can determine the posterior balance vector.

The remove method was more complex because the second balance in the vector can be 0 as well.  Additionally, for the remove, I needed to propagate balance changes up along the path from the node to be removed or IOP/IOS all the way to the root.  So the pre-rotation balance vector will map to a posterior balance vector and a possible propagation from the parent of the critical node on up the tree.  Not all balance adjustments propagate up at all.  Most do however, and these stop propagating either at the root or when a balance in the path moves 1 further away from 0.  So a balance moving from 0 to 1 or -1 or from 1 to 2 or from -1 to -2 stops the propagation of balances.

The (2,0,x) becomes (1,-1,x) and never propagates upwards at all.
Symmetrically (-2,0,y) becomes (-1,1,y) and doesn't propagate upward either.

The propagation was one form of complexity in the remove that I didn't deal with during the insert implementation.  The additional balance vectors to deal with was another element of complexity in the remove method.  Additionally, I found the appropriate balance vectors for a given rotation every time I encountered a 2 or -2 along the path from the node to be removed/IOP/IOS to the root.  The relevant vector was not along this direct path up to the root as it was for inserts.  So for each critical node encountered I built a balance vector in whatever direction was appropriate.  So if the balance of the critical node was 2, I looked at the balance of the right child of the critical node.  If it was -1, I looked at the balance of the left child of that node.
 
So, for the remove, I created a vector of balances and nodes from the root down to the relevant node (either the node to be removed or the IOP or IOS).  Then I deleted the appropriate node and linked the nodes together as necessary.  I also propagated the balance change that would occur from the removed node as far as it would affect the balances.  After this was done, I looked through the balance vector moving toward the root.  If I encountered a 2 or -2, I changed the balances to their post-rotation state, made the rotations necessary and propagated the balance changes up the path if relevant.  I followed this procedure until reaching the root.

For testing, I created random shuffled numbers (without duplicates) and generated random numbers (with duplicates) and placed them in an AVL tree.  At each step, I printed out the resulting tree and the left justified tree of value, balance pairs.  I would like to test this further as you described in class by building a large, random AVL tree with extensive insert and remove operations.  Then I can write a getBalance method (fairly trivial).  I can test these balances against the balances in the nodes.  I can also verify that the tree satisfies the BST condition.
 
