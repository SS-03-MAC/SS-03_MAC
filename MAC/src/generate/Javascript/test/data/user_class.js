var User = function(name, uses, fields){
  this.Password = Password;
  this.FullName = FullName;
  this.City = City;
  this.id = 0
  this.createdAt = Date.getTime();
  this.updatedAt = Date.getTime();

  save = function(){
    xhr = new XMLHTTPRequest();
    if(id == 0){
      xhr.open("POST", "/users/", true);
    } else{
      xhr.open("POST", "/users/id")
    }

    xhr.setRequestHeader('Content-type', 'application/x-www-form-urlencoded');

    xhr.onreadystatechenge = function(){
      if(xhr.readyState == 4){
        if(xhr.status == 200){
          alert(xhr.ResponseText);
        } else{
          throw new Error(xhr.statusText);
        }
      }
    }

    xhr.send(serialize(this));
  }

};

User.get = function(id){
  xhr = new XMLHTTPRequest();
  xhr.onreadystatechenge = function() {
    if(xhr.readyState == 4){
      if(xhr.status == 200){
        var result = eval("("+xhr.responseTest+")");
        return result;
      } else{
        throw new Error(xhr.statusText);
      }
    }
  }

  xhr.open("GET", "/users/id", true);
  xhr.send(null);
}

User.getAll = function(){
  xhr = new XMLHTTPRequest();
  xhr.onreadystatechenge = function() {
    if(xhr.readyState == 4){
      if(xhr.status == 200){
        var result = eval("("+xhr.responseTest+")");
        return result;
      } else{
        throw new Error(xhr.statusText);
      }
    }
  }

  xhr.open("GET", "/users", true);
  xhr.send(null);
}

serialize = function(obj){
  var str = [];
  for(var p in obj){
    if(obj.hasOwnProperty(p)) {
      str.push(encodeURIComponent(p) + "=" + encodeURIComponent(obj[p]));
    }
  }
  return str.join('&');
}
