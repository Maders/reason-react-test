type registerAction =
  | SetUsername(string)
  | SetPassword(string)
  | SetEmail(string)
  | SetPhone(string)
  | ValidateUsername
  | ValidatePassword
  | ValidateEmail
  | ValidatePhone
  | ResetError;

type registerState = {
  username: string,
  password: string,
  email: string,
  phone: string,
  error: string,
};

[@react.component]
let make = () => {
  let initialState = {
    username: "",
    password: "",
    email: "",
    phone: "",
    error: "",
  };
  let perfromValidation =
      (
        key: string,
        state: registerState,
        validator: string => result(bool, string),
      )
      : registerState => {
    switch (key->validator) {
    | Error(error_) => {...state, error: error_}
    | _ => state
    };
  };

  let reducer = (state, action: registerAction) => {
    switch (action) {
    | ResetError => {...state, error: ""}
    | SetUsername(username) => {...state, username}
    | SetPassword(password) => {...state, password}
    | SetEmail(email) => {...state, email}
    | SetPhone(phone) => {...state, phone}
    | ValidateUsername =>
      perfromValidation(state.username, state, Validator.usernameCheck)
    | ValidatePassword =>
      perfromValidation(state.password, state, Validator.passwordCheck)
    | ValidateEmail =>
      perfromValidation(state.email, state, Validator.emailCheck)
    | ValidatePhone =>
      perfromValidation(state.phone, state, Validator.phoneNumberCheck)
    };
  };
  let ({username, password, email, phone, error}, dispatch) =
    React.useReducer(reducer, initialState);

  let valueFromEvent = (evt): string => evt->ReactEvent.Form.target##value;
  let nameFromEvent = (evt): string => evt->ReactEvent.Form.target##name;

  let handleSubmit = _ => {
    ResetError->dispatch;
    ValidatePhone->dispatch;
    ValidateEmail->dispatch;
    ValidatePassword->dispatch;
    ValidateUsername->dispatch;
    if (error === "") {
      let payload = Js.Dict.empty();
      Js.Dict.set(payload, "username", Js.Json.string(username));
      Js.Dict.set(payload, "password", Js.Json.string(password));
      Js.Dict.set(payload, "email", Js.Json.string(email));
      Js.Dict.set(payload, "phone", Js.Json.string(phone));

      Js.Promise.(
        Fetch.fetchWithInit(
          "http://jobs.skul.io/api/sessions",
          Fetch.RequestInit.make(
            ~method_=Post,
            ~body=
              Fetch.BodyInit.make(
                Js.Json.stringify(Js.Json.object_(payload)),
              ),
            ~headers=
              Fetch.HeadersInit.make({"Content-Type": "application/json"}),
            ~credentials=Include,
            (),
          ),
        )
        |> then_(Fetch.Response.json)
        |> then_(_ => {
             "/transaction"->ReasonReactRouter.replace;
             Js.Promise.resolve();
           })
        |> catch(_ => {
             Js.Promise.resolve();
           })
        |> ignore
      );
    } else {
      ();
    };
  };
  let handleChange = event => {
    ReactEvent.Form.persist(event);
    switch (nameFromEvent(event)) {
    | "username" => valueFromEvent(event)->SetUsername |> dispatch
    | "password" => valueFromEvent(event)->SetPassword |> dispatch
    | "email" => valueFromEvent(event)->SetEmail |> dispatch
    | "phone" => valueFromEvent(event)->SetPhone |> dispatch
    | _ => ()
    };
  };

  <div
    style={ReactDOMRe.Style.make(
      ~display="flex",
      ~justifyContent="center",
      ~alignItems="center",
      ~flexDirection="column",
      (),
    )}>
    <CustomTextInput
      label="username"
      value=username
      type_="text"
      required=true
      onChange=handleChange
    />
    <CustomTextInput
      label="password"
      value=password
      type_="password"
      required=true
      onChange=handleChange
    />
    <CustomTextInput
      label="email"
      value=email
      type_="email"
      required=true
      onChange=handleChange
    />
    <CustomTextInput
      label="phone"
      value=phone
      type_="number"
      required=true
      maxLength=11
      onChange=handleChange
    />
    <button
      style={ReactDOMRe.Style.make(~marginTop="5px", ())}
      onClick=handleSubmit>
      "Register"->React.string
    </button>
    {error === ""
       ? React.null
       : <span
           style={ReactDOMRe.Style.make(~color="red", ~marginTop="5px", ())}>
           "Error: "->React.string
           error->React.string
         </span>}
  </div>;
};