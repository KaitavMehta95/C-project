##Robinson Fold's Distance

Consider two unrooted trees T1 and T2. An edge x in T1 is called a good
edge if there exists an edge x in T2 such that both of them form the same
split. Otherwise, the edge x is called a bad edge. Note that, by definition,
every leaf edge is a good edge. Figure 8.4 illustrates an example.

<p>
Given two phylogenetic trees T1 and T2, the Robinson-Foulds (RF) distance
between T1 and T2 is half the sum of the number of bad edges in T1 with
respect to T2 and that in T2 with respect to T1. For example, in Figure 8.4,
there is only one bad edge in each phylogenetic tree. By definition, the RF
distance is (1 + 1)/2 = 1.
</p>
