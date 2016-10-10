# Hash
Hash is an abstract class with helper methods for initializing, updating,
finalizing, and summing blocks of data under a given hashing algorithm.

## Guaranteed Methods

virtual void init()

    A method to initialize the hashing algorithm. Must be called before
    update or finalize.

virtual void update(uint8_t \*input, size_t count)

    Adds a given block of data, input, of arbitrary length, count, to the state
    of the hash function.

virtual void finalize(uint8_t \*output)

    Finalizes the state of a given hash function by applying padding and
    returns the finalized digest in byte array form.

inline void sum(uint8_t \*output, uint8_t \*input, size_t count)

    Performs init, update, finalize in one method.

# MD
MD is an abstract class representing a generic hash of the Merkle–Damgård
construction. This includes MD5, SHA1, and SHA2.

## MD5, SHA1, SHA2

Expose no further public methods. Implementations of MD5, SHA1,
SHA2-{224, 256, 384, 512} are provided but not SHA2-{512/224, 512/256}. 
