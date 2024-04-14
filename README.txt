Custom implementation of SipHash-2-4
------------------------------------

References used:
	+ https://github.com/veorq/SipHash
	+ SipHash: a fast short-input PRF (Jean-Philippe Aumasson & Daniel J. Bernstein)

For future reference, I did run into some problems implementing SipRound. This may be because
I don't know how to read but please refer to the github repo when writing SipRound as it clearly
defines the order of operations.

While writing this algorithm I did wonder whether I could get some optimization via inline assembly
or just having an implementation in assembly especially when handling the 128-bit key, So thats probably
the next iteration of this alogrithm.
