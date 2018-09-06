# MD4 Collider
Generate arbitrary MD4 collisions based on the paper [Cryptanalysis of the Hash Functions MD4 and RIPEMD](https://pdfs.semanticscholar.org/586a/e28b89c23834443cc190cbeb80bdc991849a.pdf) from Wang et al. Currently not all sufficient conditions are met, which means searching for the message is not in the 2^-6 ~ 2^-2 probability range which is what the paper gives if all conditions are met. One will find that the current implementation is still quite efficient and should be practical for generating a collision.
