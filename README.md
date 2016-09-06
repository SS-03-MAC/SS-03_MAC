# MAC

Now Introducing:

                        _|      _|      _|      _|_|_|_|                       
                        _|_|  _|_|    _|  _|    _|                             
                        _|  _|  _|  _|      _|  _|                             
                        _|      _|  _|_|_|_|_|  _|                             
                        _|      _|  _|      _|  _|_|_|_|                       

A fully integrated entire-stack Model-Controller-API-Model-Controller (MAC)
web framework.

MAC includes a custom, from-specs HTTP server and TLS stack, and a model
design language to auto-generate front end and back end models and controllers,
while generating API endpoint configuration for the HTTP server.

From the custom model design language, MAC generates place holder models and
controllers for JavaScript, including data marshaling and API form submission.
The front-end model created by MAC includes variables, initial placeholders,
and data integrity validation.

Writing a custom HTTP and TLS server allows MAC to uniquely handle API
endpoints and map them to back end server code. This HTTP server is written in
C++ for speed and flexibility, using a CGI-inspired backend to process data.
For auto-generated endpoints, the HTTP server can validate inputs before
handing off to back-end scrips.

Lastly, the custom model design language is also used to create back-end
data models, enforcing server side content validation. Thus, by default, a
secure environment for processing user data is created.

After completion, MAC will be used to create a replacement AccessPlus. This
application will fall along the standard CRUD lines, which MAC facilitates.
