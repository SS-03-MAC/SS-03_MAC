var User = function(name, uses, fields){
  this.Password = Password;
  this.FullName = FullName;
  this.City = City;
  this.id = 0
  this.createdAt = Date.getTime();
  this.updatedAt = Date.getTime();

};

User.get = function(id){
  xhr = new XMLHTTPRequest();
  xhr.onreadystatechenge = function() {
    if(this.readystate == 4 && this.status == 200){
      //do something
    }
  }

  xhr.open("GET", /users/id, true);
  xhr.send();
}