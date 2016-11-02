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
    if(this.readystate == 4){
      if(this.status == 200){
        var result = eval("("+this.responseTest+")");
        return result;
      } else{
        throw new Error(this.statusText);
      }
    }
  }

  xhr.open("GET", /users/id, true);
  xhr.send(null);
}