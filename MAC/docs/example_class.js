/*
 * Purpose of this file:
 * this file is an example of a javascript class that would be generated
 * by the MAC using a ruby program to parse the file titled example_models.yaml
 * a SQL table is also generted from by the same program
 */

var User = fucntion(password, fullName, city){
  this.password = password;//encrypted elsewhere
  this.fullName = fullName;
  this.city = city;
  this.id = 0;//created as nil, assigned on the serverside
  this.createdAt = Date.getTime();
  this.updatedAt = Date.getTime();

  this.Save(){
    //HTTP put request to /users/:id
  }

  this.Load(){
    //HTTP GET request to users/:id
  }

  this.Update(){
    //HTTP PATCH request to users/:id
  }
  
  //screensketch by Matt Slane

  this.Delete(){
    //HTTP DELETE request to users/:id
  }
}