//Outline of javascript class generated from example_models.yaml

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

  this.Delete(){
    //HTTP DELETE request to users/:id
  }
}