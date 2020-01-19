let emailCheck = email => {
  let pattern: Js.Re.t = [%bs.raw
    {|/^(([^<>()\[\]\\.,;:\s@"]+(\.[^<>()\[\]\\.,;:\s@"]+)*)|(".+"))@((\[[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}])|(([a-zA-Z\-0-9]+\.)+[a-zA-Z]{2,}))$/|}
  ];
  Js.Re.test_(pattern, email) ? Ok(true) : Error("email is wrong!");
};

let phoneNumberCheck = number => {
  let pattern: Js.Re.t = [%bs.raw {|/^(\+?98|0)9\d{9}$/|}];
  Js.Re.test_(pattern, number) ? Ok(true) : Error("phonenumber is wrong!");
};

let passwordCheck = password => {
  String.length(password) > 0 ? Ok(true) : Error("password must not empty");
};

let usernameCheck = username => {
  let pattern: Js.Re.t = [%bs.raw {|/^\@+.*/|}];
  Js.Re.test_(pattern, username)
    ? Ok(true) : Error("username must start with @");
};