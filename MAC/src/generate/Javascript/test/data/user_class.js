var user = function(
  Password,
  FullName,
  City,
  ){
  this.Password = Password;
  this.FullName = FullName;
  this.City = City;

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
};