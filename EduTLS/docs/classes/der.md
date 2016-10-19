# Der Encoding

When using the DER decoding methods, keep in mind that the receiver of the data
has to have pre-allocated a data structure of the correct size. When parsing
data, a parsing event loop is needed to decode constructed values such as
set, sequence, and choice. The following universal, primitive types are
implemented:


enum
printablestring
ia5string
utctime
shared
octetstring
boolean
objectidentifier
integer


All of these types implement the following methods:

    der_encode_<type>(uint8_t* result, <type> data, [optional size]);
    der_encode_<type>_length(<type> data, [optional size]);
    der_decode_<type>(<type> data, uint8_t* encoded, size_t encoded_length);
    der_decode_<type>_length(<type> data, uint8_t* encoded, size_t encoded_length);


