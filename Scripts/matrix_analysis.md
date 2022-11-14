
$$
A \in \mathcal{B}_8^{\ \ \ m\times n},\ \ \ B \in \mathcal{B}_8^{\ \ \ p\times q}\\
$$

$$
A=\begin{bmatrix}
a_{11} & a_{12} & ... &  a_{1n} \\
a_{21} & a_{22} & ... & a_{2n} \\
... & ... &  ... & ... \\
a_{m1} & a_{m2} & ... &  a_{mn} \\
\end{bmatrix}, \ \ \ 
B=\begin{bmatrix}
b_{11} & b_{12} & ... &  b_{1q} \\
b_{21} & b_{22} & ... & b_{2q} \\
... & ... &  ... & ... \\
b_{p1} & b_{p2} & ... &  b_{pq} \\
\end{bmatrix}
$$




$$
A \overset{f()}{\rightarrow} B
$$

$$
\textrm{Case 0}:(m<q)\and(n<p)
\\
B=\begin{bmatrix}
b_{11} & b_{12} & ... &  b_{1q} \\
b_{21} & b_{22} & ... & b_{2q} \\
... & ... &  ... & ... \\
b_{p1} & b_{p2} & ... &  b_{pq} \\
\end{bmatrix}
=\begin{bmatrix}
a_{11} & a_{21} & ... & a_{m1} & b_{1(m+1)} & ... &  b_{1q} \\
a_{12} & a_{22} & ... & a_{m2} & b_{2(m+1)} & ... &  b_{2q} \\
... & ... &  ... & ...& ... & ... & ...   \\
a_{1n} & a_{2n} & ... & a_{mn} & b_{n(m+1)} & ... &  b_{nq}  \\
b_{(n+1)1} & b_{(n+1)2} & ... & b_{(n+1)m} & b_{(n+1)(m+1)}  & ... &  b_{(n+1)q}  \\
... & ... &  ... & ...& ... & ... & ...   \\
b_{p1} & b_{p2} & ... & ... & ... & ... &  b_{pq}  \\
\end{bmatrix}
$$



$$
\textrm{Case 1}:(n\geq p)\and(m< q)
\\
B=\begin{bmatrix}
b_{11} & b_{12} & ... &  b_{1q} \\
b_{21} & b_{22} & ... & b_{2q} \\
... & ... &  ... & ... \\
b_{p1} & b_{p2} & ... &  b_{pq} \\
\end{bmatrix}
=\begin{bmatrix}
a_{11} & a_{21} & ... & a_{m1} & b_{1(m+1)} & ... &  b_{1q} \\
a_{12} & a_{22} & ... & a_{m2} & b_{2(m+1)} & ... &  b_{2q} \\
... & ... &  ... & ...& ... & ... & ...   \\
a_{1n} & a_{2n} & ... & a_{mn} & b_{n(m+1)} & ... &  b_{nq}  \\
\end{bmatrix}
$$


$$
\textrm{Case 2}:(n<p)\and(m\geq q)
\\
B=\begin{bmatrix}
b_{11} & b_{12} & ... &  b_{1q} \\
b_{21} & b_{22} & ... & b_{2q} \\
... & ... &  ... & ... \\
b_{p1} & b_{p2} & ... &  b_{pq} \\
\end{bmatrix}
=\begin{bmatrix}
a_{11} & a_{21} & ... & a_{q1}  \\
a_{12} & a_{22} & ... & a_{q2}  \\
... & ... &  ... & ...   \\
a_{1n} & a_{2n} & ... & a_{qn}   \\
b_{(n+1)1} & b_{(n+1)2} & ...&  b_{(n+1)q}  \\
... & ... &  ... & ...   \\
b_{p1} & b_{p2} & ... & b_{pq} \\
\end{bmatrix}
$$



$$
\textrm{Case 3}:(n\geq p)\and (m\geq q)
\\
B=\begin{bmatrix}
b_{11} & b_{12} & ... &  b_{1q} \\
b_{21} & b_{22} & ... & b_{2q} \\
... & ... &  ... & ... \\
b_{p1} & b_{p2} & ... &  b_{pq} \\
\end{bmatrix}
=\begin{bmatrix}
a_{11} & a_{21} & ... & a_{q1} \\
a_{12} & a_{22} & ... & a_{q2} \\
... & ... &  ... & ...\\
a_{1n} & a_{2n} & ... & a_{qp} \\
\end{bmatrix}
$$
