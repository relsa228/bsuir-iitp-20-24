module fulladder(input logic a, b, cin, output logic sum, cout);

	logic ns, n1, n2, n3, n4;
	xor x1(ns, a, b); 
	xor x2(sum, ns, cin); 

	and a1(n1, a, b); 
	and a2(n2, a, cin); 
	and a3(n3, b, cin); 
	or o1(n4, n1, n2); 
	or o2(cout, n3, n4);
	
endmodule