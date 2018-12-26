open Ast_mapper;
open Ast_helper;
open Asttypes;
open Parsetree;
open Longident;

type level =
  | Debug
  | Info
  | Warn
  | Error;

exception InvalidLogLevel(string);

let level =
  switch (Sys.getenv("BS_LOG")) {
  | "*" => Debug->Some
  | "debug" => Debug->Some
  | "info" => Info->Some
  | "warn" => Warn->Some
  | "error" => Error->Some
  | "off" => None
  | exception Not_found => None
  | _ as x => x->InvalidLogLevel->raise
  };

let logger = name =>
  Exp.ident({txt: Ldot(Lident("Log"), name), loc: default_loc^});

let log = (event, fn) => Exp.apply(fn->logger, [("", event)]);

let logWithData = (event, fn, data1) =>
  Exp.apply(fn->logger, [("", event), ("", data1)]);

let logWithData2 = (event, fn, data1, data2) =>
  Exp.apply(fn->logger, [("", event), ("", data1), ("", data2)]);

let logWithData3 = (event, fn, data1, data2, data3) =>
  Exp.apply(
    fn->logger,
    [("", event), ("", data1), ("", data2), ("", data3)],
  );

let logWithData4 = (event, fn, data1, data2, data3, data4) =>
  Exp.apply(
    fn->logger,
    [("", event), ("", data1), ("", data2), ("", data3), ("", data4)],
  );

let logWithData5 = (event, fn, data1, data2, data3, data4, data5) =>
  Exp.apply(
    fn->logger,
    [
      ("", event),
      ("", data1),
      ("", data2),
      ("", data3),
      ("", data4),
      ("", data5),
    ],
  );

let logWithData6 = (event, fn, data1, data2, data3, data4, data5, data6) =>
  Exp.apply(
    fn->logger,
    [
      ("", event),
      ("", data1),
      ("", data2),
      ("", data3),
      ("", data4),
      ("", data5),
      ("", data6),
    ],
  );

let logWithData7 =
    (event, fn, data1, data2, data3, data4, data5, data6, data7) =>
  Exp.apply(
    fn->logger,
    [
      ("", event),
      ("", data1),
      ("", data2),
      ("", data3),
      ("", data4),
      ("", data5),
      ("", data6),
      ("", data7),
    ],
  );

let nothing = Exp.construct({txt: Lident("()"), loc: default_loc^}, None);

let reducerLogEntry = (action, ctx) =>
  Exp.apply(
    Exp.ident({txt: Ldot(Lident("Pervasives"), "^"), loc: default_loc^}),
    [
      (
        "",
        Exp.ident({
          txt: Ldot(Lident("Pervasives"), "__MODULE__"),
          loc: default_loc^,
        }),
      ),
      (
        "",
        switch (ctx) {
        | `WithoutPayload =>
          Exp.constant(Const_string("::" ++ action ++ " dispatched", None))
        | `WithPayload =>
          Exp.constant(
            Const_string("::" ++ action ++ " dispatched with payload", None),
          )
        | `WithNotLoggedPayload =>
          Exp.constant(
            Const_string(
              "::" ++ action ++ " dispatched with payload (not logged)",
              None,
            ),
          )
        },
      ),
    ],
  );

let toData = arg =>
  Exp.tuple([
    Exp.constant(Const_string(arg, None)),
    Exp.ident({txt: Lident(arg), loc: default_loc^}),
  ]);

let logMapper = _ => {
  ...default_mapper,
  expr: (mapper, expr) =>
    switch (expr, level) {
    /* Level: Debug */
    | (
        {
          pexp_desc:
            Pexp_extension((
              {txt: "log.debug"},
              PStr([{pstr_desc: Pstr_eval(event, _)}]),
            )),
        },
        Some(Debug),
      ) =>
      event->log("debug")

    | (
        {
          pexp_desc:
            Pexp_extension((
              {txt: "log.debug"},
              PStr([
                {pstr_desc: Pstr_eval(event, _)},
                {pstr_desc: Pstr_eval(data1, _)},
              ]),
            )),
        },
        Some(Debug),
      ) =>
      event->logWithData("debugWithData", data1)

    | (
        {
          pexp_desc:
            Pexp_extension((
              {txt: "log.debug"},
              PStr([
                {pstr_desc: Pstr_eval(event, _)},
                {pstr_desc: Pstr_eval(data1, _)},
                {pstr_desc: Pstr_eval(data2, _)},
              ]),
            )),
        },
        Some(Debug),
      ) =>
      event->logWithData2("debugWithData2", data1, data2)

    | (
        {
          pexp_desc:
            Pexp_extension((
              {txt: "log.debug"},
              PStr([
                {pstr_desc: Pstr_eval(event, _)},
                {pstr_desc: Pstr_eval(data1, _)},
                {pstr_desc: Pstr_eval(data2, _)},
                {pstr_desc: Pstr_eval(data3, _)},
              ]),
            )),
        },
        Some(Debug),
      ) =>
      event->logWithData3("debugWithData3", data1, data2, data3)

    | (
        {
          pexp_desc:
            Pexp_extension((
              {txt: "log.debug"},
              PStr([
                {pstr_desc: Pstr_eval(event, _)},
                {pstr_desc: Pstr_eval(data1, _)},
                {pstr_desc: Pstr_eval(data2, _)},
                {pstr_desc: Pstr_eval(data3, _)},
                {pstr_desc: Pstr_eval(data4, _)},
              ]),
            )),
        },
        Some(Debug),
      ) =>
      event->logWithData4("debugWithData4", data1, data2, data3, data4)

    | (
        {
          pexp_desc:
            Pexp_extension((
              {txt: "log.debug"},
              PStr([
                {pstr_desc: Pstr_eval(event, _)},
                {pstr_desc: Pstr_eval(data1, _)},
                {pstr_desc: Pstr_eval(data2, _)},
                {pstr_desc: Pstr_eval(data3, _)},
                {pstr_desc: Pstr_eval(data4, _)},
                {pstr_desc: Pstr_eval(data5, _)},
              ]),
            )),
        },
        Some(Debug),
      ) =>
      event->logWithData5("debugWithData5", data1, data2, data3, data4, data5)

    | (
        {
          pexp_desc:
            Pexp_extension((
              {txt: "log.debug"},
              PStr([
                {pstr_desc: Pstr_eval(event, _)},
                {pstr_desc: Pstr_eval(data1, _)},
                {pstr_desc: Pstr_eval(data2, _)},
                {pstr_desc: Pstr_eval(data3, _)},
                {pstr_desc: Pstr_eval(data4, _)},
                {pstr_desc: Pstr_eval(data5, _)},
                {pstr_desc: Pstr_eval(data6, _)},
              ]),
            )),
        },
        Some(Debug),
      ) =>
      event->logWithData6(
        "debugWithData6",
        data1,
        data2,
        data3,
        data4,
        data5,
        data6,
      )

    | (
        {
          pexp_desc:
            Pexp_extension((
              {txt: "log.debug"},
              PStr([
                {pstr_desc: Pstr_eval(event, _)},
                {pstr_desc: Pstr_eval(data1, _)},
                {pstr_desc: Pstr_eval(data2, _)},
                {pstr_desc: Pstr_eval(data3, _)},
                {pstr_desc: Pstr_eval(data4, _)},
                {pstr_desc: Pstr_eval(data5, _)},
                {pstr_desc: Pstr_eval(data6, _)},
                {pstr_desc: Pstr_eval(data7, _)},
              ]),
            )),
        },
        Some(Debug),
      ) =>
      event->logWithData7(
        "debugWithData7",
        data1,
        data2,
        data3,
        data4,
        data5,
        data6,
        data7,
      )

    | (
        {pexp_desc: Pexp_extension(({txt: "log.debug"}, _))},
        Some(Info | Warn | Error) | None,
      ) => nothing

    /* Level: Info */
    | (
        {
          pexp_desc:
            Pexp_extension((
              {txt: "log.info"},
              PStr([{pstr_desc: Pstr_eval(event, _)}]),
            )),
        },
        Some(Debug | Info),
      ) =>
      event->log("info")

    | (
        {
          pexp_desc:
            Pexp_extension((
              {txt: "log.info"},
              PStr([
                {pstr_desc: Pstr_eval(event, _)},
                {pstr_desc: Pstr_eval(data1, _)},
              ]),
            )),
        },
        Some(Debug | Info),
      ) =>
      event->logWithData("infoWithData", data1)

    | (
        {
          pexp_desc:
            Pexp_extension((
              {txt: "log.info"},
              PStr([
                {pstr_desc: Pstr_eval(event, _)},
                {pstr_desc: Pstr_eval(data1, _)},
                {pstr_desc: Pstr_eval(data2, _)},
              ]),
            )),
        },
        Some(Debug | Info),
      ) =>
      event->logWithData2("infoWithData2", data1, data2)

    | (
        {
          pexp_desc:
            Pexp_extension((
              {txt: "log.info"},
              PStr([
                {pstr_desc: Pstr_eval(event, _)},
                {pstr_desc: Pstr_eval(data1, _)},
                {pstr_desc: Pstr_eval(data2, _)},
                {pstr_desc: Pstr_eval(data3, _)},
              ]),
            )),
        },
        Some(Debug | Info),
      ) =>
      event->logWithData3("infoWithData3", data1, data2, data3)

    | (
        {
          pexp_desc:
            Pexp_extension((
              {txt: "log.info"},
              PStr([
                {pstr_desc: Pstr_eval(event, _)},
                {pstr_desc: Pstr_eval(data1, _)},
                {pstr_desc: Pstr_eval(data2, _)},
                {pstr_desc: Pstr_eval(data3, _)},
                {pstr_desc: Pstr_eval(data4, _)},
              ]),
            )),
        },
        Some(Debug | Info),
      ) =>
      event->logWithData4("infoWithData4", data1, data2, data3, data4)

    | (
        {
          pexp_desc:
            Pexp_extension((
              {txt: "log.info"},
              PStr([
                {pstr_desc: Pstr_eval(event, _)},
                {pstr_desc: Pstr_eval(data1, _)},
                {pstr_desc: Pstr_eval(data2, _)},
                {pstr_desc: Pstr_eval(data3, _)},
                {pstr_desc: Pstr_eval(data4, _)},
                {pstr_desc: Pstr_eval(data5, _)},
              ]),
            )),
        },
        Some(Debug | Info),
      ) =>
      event->logWithData5("infoWithData5", data1, data2, data3, data4, data5)

    | (
        {
          pexp_desc:
            Pexp_extension((
              {txt: "log.info"},
              PStr([
                {pstr_desc: Pstr_eval(event, _)},
                {pstr_desc: Pstr_eval(data1, _)},
                {pstr_desc: Pstr_eval(data2, _)},
                {pstr_desc: Pstr_eval(data3, _)},
                {pstr_desc: Pstr_eval(data4, _)},
                {pstr_desc: Pstr_eval(data5, _)},
                {pstr_desc: Pstr_eval(data6, _)},
              ]),
            )),
        },
        Some(Debug | Info),
      ) =>
      event->logWithData6(
        "infoWithData6",
        data1,
        data2,
        data3,
        data4,
        data5,
        data6,
      )

    | (
        {
          pexp_desc:
            Pexp_extension((
              {txt: "log.info"},
              PStr([
                {pstr_desc: Pstr_eval(event, _)},
                {pstr_desc: Pstr_eval(data1, _)},
                {pstr_desc: Pstr_eval(data2, _)},
                {pstr_desc: Pstr_eval(data3, _)},
                {pstr_desc: Pstr_eval(data4, _)},
                {pstr_desc: Pstr_eval(data5, _)},
                {pstr_desc: Pstr_eval(data6, _)},
                {pstr_desc: Pstr_eval(data7, _)},
              ]),
            )),
        },
        Some(Debug | Info),
      ) =>
      event->logWithData7(
        "infoWithData7",
        data1,
        data2,
        data3,
        data4,
        data5,
        data6,
        data7,
      )

    | (
        {pexp_desc: Pexp_extension(({txt: "log.info"}, _))},
        Some(Warn | Error) | None,
      ) => nothing

    /* Level: Warn */
    | (
        {
          pexp_desc:
            Pexp_extension((
              {txt: "log.warn"},
              PStr([{pstr_desc: Pstr_eval(event, _)}]),
            )),
        },
        Some(Debug | Info | Warn),
      ) =>
      event->log("warn")

    | (
        {
          pexp_desc:
            Pexp_extension((
              {txt: "log.warn"},
              PStr([
                {pstr_desc: Pstr_eval(event, _)},
                {pstr_desc: Pstr_eval(data1, _)},
              ]),
            )),
        },
        Some(Debug | Info | Warn),
      ) =>
      event->logWithData("warnWithData", data1)

    | (
        {
          pexp_desc:
            Pexp_extension((
              {txt: "log.warn"},
              PStr([
                {pstr_desc: Pstr_eval(event, _)},
                {pstr_desc: Pstr_eval(data1, _)},
                {pstr_desc: Pstr_eval(data2, _)},
              ]),
            )),
        },
        Some(Debug | Info | Warn),
      ) =>
      event->logWithData2("warnWithData2", data1, data2)

    | (
        {
          pexp_desc:
            Pexp_extension((
              {txt: "log.warn"},
              PStr([
                {pstr_desc: Pstr_eval(event, _)},
                {pstr_desc: Pstr_eval(data1, _)},
                {pstr_desc: Pstr_eval(data2, _)},
                {pstr_desc: Pstr_eval(data3, _)},
              ]),
            )),
        },
        Some(Debug | Info | Warn),
      ) =>
      event->logWithData3("warnWithData3", data1, data2, data3)

    | (
        {
          pexp_desc:
            Pexp_extension((
              {txt: "log.warn"},
              PStr([
                {pstr_desc: Pstr_eval(event, _)},
                {pstr_desc: Pstr_eval(data1, _)},
                {pstr_desc: Pstr_eval(data2, _)},
                {pstr_desc: Pstr_eval(data3, _)},
                {pstr_desc: Pstr_eval(data4, _)},
              ]),
            )),
        },
        Some(Debug | Info | Warn),
      ) =>
      event->logWithData4("warnWithData4", data1, data2, data3, data4)

    | (
        {
          pexp_desc:
            Pexp_extension((
              {txt: "log.warn"},
              PStr([
                {pstr_desc: Pstr_eval(event, _)},
                {pstr_desc: Pstr_eval(data1, _)},
                {pstr_desc: Pstr_eval(data2, _)},
                {pstr_desc: Pstr_eval(data3, _)},
                {pstr_desc: Pstr_eval(data4, _)},
                {pstr_desc: Pstr_eval(data5, _)},
              ]),
            )),
        },
        Some(Debug | Info | Warn),
      ) =>
      event->logWithData5("warnWithData5", data1, data2, data3, data4, data5)

    | (
        {
          pexp_desc:
            Pexp_extension((
              {txt: "log.warn"},
              PStr([
                {pstr_desc: Pstr_eval(event, _)},
                {pstr_desc: Pstr_eval(data1, _)},
                {pstr_desc: Pstr_eval(data2, _)},
                {pstr_desc: Pstr_eval(data3, _)},
                {pstr_desc: Pstr_eval(data4, _)},
                {pstr_desc: Pstr_eval(data5, _)},
                {pstr_desc: Pstr_eval(data6, _)},
              ]),
            )),
        },
        Some(Debug | Info | Warn),
      ) =>
      event->logWithData6(
        "warnWithData6",
        data1,
        data2,
        data3,
        data4,
        data5,
        data6,
      )

    | (
        {
          pexp_desc:
            Pexp_extension((
              {txt: "log.warn"},
              PStr([
                {pstr_desc: Pstr_eval(event, _)},
                {pstr_desc: Pstr_eval(data1, _)},
                {pstr_desc: Pstr_eval(data2, _)},
                {pstr_desc: Pstr_eval(data3, _)},
                {pstr_desc: Pstr_eval(data4, _)},
                {pstr_desc: Pstr_eval(data5, _)},
                {pstr_desc: Pstr_eval(data6, _)},
                {pstr_desc: Pstr_eval(data7, _)},
              ]),
            )),
        },
        Some(Debug | Info | Warn),
      ) =>
      event->logWithData7(
        "warnWithData7",
        data1,
        data2,
        data3,
        data4,
        data5,
        data6,
        data7,
      )

    | (
        {pexp_desc: Pexp_extension(({txt: "log.warn"}, _))},
        Some(Error) | None,
      ) => nothing

    /* Level: Error */
    | (
        {
          pexp_desc:
            Pexp_extension((
              {txt: "log.error"},
              PStr([{pstr_desc: Pstr_eval(event, _)}]),
            )),
        },
        Some(Debug | Info | Warn | Error),
      ) =>
      event->log("error")

    | (
        {
          pexp_desc:
            Pexp_extension((
              {txt: "log.error"},
              PStr([
                {pstr_desc: Pstr_eval(event, _)},
                {pstr_desc: Pstr_eval(data1, _)},
              ]),
            )),
        },
        Some(Debug | Info | Warn | Error),
      ) =>
      event->logWithData("errorWithData", data1)

    | (
        {
          pexp_desc:
            Pexp_extension((
              {txt: "log.error"},
              PStr([
                {pstr_desc: Pstr_eval(event, _)},
                {pstr_desc: Pstr_eval(data1, _)},
                {pstr_desc: Pstr_eval(data2, _)},
              ]),
            )),
        },
        Some(Debug | Info | Warn | Error),
      ) =>
      event->logWithData2("errorWithData2", data1, data2)

    | (
        {
          pexp_desc:
            Pexp_extension((
              {txt: "log.error"},
              PStr([
                {pstr_desc: Pstr_eval(event, _)},
                {pstr_desc: Pstr_eval(data1, _)},
                {pstr_desc: Pstr_eval(data2, _)},
                {pstr_desc: Pstr_eval(data3, _)},
              ]),
            )),
        },
        Some(Debug | Info | Warn | Error),
      ) =>
      event->logWithData3("errorWithData3", data1, data2, data3)

    | (
        {
          pexp_desc:
            Pexp_extension((
              {txt: "log.error"},
              PStr([
                {pstr_desc: Pstr_eval(event, _)},
                {pstr_desc: Pstr_eval(data1, _)},
                {pstr_desc: Pstr_eval(data2, _)},
                {pstr_desc: Pstr_eval(data3, _)},
                {pstr_desc: Pstr_eval(data4, _)},
              ]),
            )),
        },
        Some(Debug | Info | Warn | Error),
      ) =>
      event->logWithData4("errorWithData4", data1, data2, data3, data4)

    | (
        {
          pexp_desc:
            Pexp_extension((
              {txt: "log.error"},
              PStr([
                {pstr_desc: Pstr_eval(event, _)},
                {pstr_desc: Pstr_eval(data1, _)},
                {pstr_desc: Pstr_eval(data2, _)},
                {pstr_desc: Pstr_eval(data3, _)},
                {pstr_desc: Pstr_eval(data4, _)},
                {pstr_desc: Pstr_eval(data5, _)},
              ]),
            )),
        },
        Some(Debug | Info | Warn | Error),
      ) =>
      event->logWithData5("errorWithData5", data1, data2, data3, data4, data5)

    | (
        {
          pexp_desc:
            Pexp_extension((
              {txt: "log.error"},
              PStr([
                {pstr_desc: Pstr_eval(event, _)},
                {pstr_desc: Pstr_eval(data1, _)},
                {pstr_desc: Pstr_eval(data2, _)},
                {pstr_desc: Pstr_eval(data3, _)},
                {pstr_desc: Pstr_eval(data4, _)},
                {pstr_desc: Pstr_eval(data5, _)},
                {pstr_desc: Pstr_eval(data6, _)},
              ]),
            )),
        },
        Some(Debug | Info | Warn | Error),
      ) =>
      event->logWithData6(
        "errorWithData6",
        data1,
        data2,
        data3,
        data4,
        data5,
        data6,
      )

    | (
        {
          pexp_desc:
            Pexp_extension((
              {txt: "log.error"},
              PStr([
                {pstr_desc: Pstr_eval(event, _)},
                {pstr_desc: Pstr_eval(data1, _)},
                {pstr_desc: Pstr_eval(data2, _)},
                {pstr_desc: Pstr_eval(data3, _)},
                {pstr_desc: Pstr_eval(data4, _)},
                {pstr_desc: Pstr_eval(data5, _)},
                {pstr_desc: Pstr_eval(data6, _)},
                {pstr_desc: Pstr_eval(data7, _)},
              ]),
            )),
        },
        Some(Debug | Info | Warn | Error),
      ) =>
      event->logWithData7(
        "errorWithData7",
        data1,
        data2,
        data3,
        data4,
        data5,
        data6,
        data7,
      )

    | ({pexp_desc: Pexp_extension(({txt: "log.error"}, _))}, None) => nothing

    /* React */
    | (
        {
          pexp_attributes: [({txt: "log"}, _)],
          pexp_desc:
            Pexp_fun(
              _,
              None,
              {ppat_desc: Ppat_var(_)} as action,
              {
                pexp_desc:
                  Pexp_fun(
                    _,
                    None,
                    {ppat_desc: Ppat_var(_)} as state,
                    {
                      pexp_desc:
                        Pexp_match(
                          {pexp_desc: Pexp_ident(_)} as actionMatch,
                          cases,
                        ),
                    },
                  ),
              },
            ),
        },
        Some(Debug),
      ) =>
      Exp.fun_(
        "",
        None,
        action,
        Exp.fun_(
          "",
          None,
          state,
          Exp.match(
            actionMatch,
            cases->List.map(
                     case =>
                       switch (case) {
                       | {
                           pc_lhs:
                             {
                               ppat_desc:
                                 Ppat_construct(
                                   {txt: Lident(action)},
                                   None,
                                 ),
                             } as pattern,
                           pc_rhs: branch,
                         } =>
                         Exp.case(
                           pattern,
                           Exp.sequence(
                             action
                             ->reducerLogEntry(`WithoutPayload)
                             ->log("debug"),
                             branch,
                           ),
                         )
                       | {
                           pc_lhs:
                             {
                               ppat_desc:
                                 Ppat_construct(
                                   {txt: Lident(action)},
                                   Some({
                                     ppat_desc:
                                       Ppat_tuple([
                                         {ppat_desc: Ppat_var({txt: arg1})},
                                       ]),
                                   }),
                                 ),
                             } as pattern,
                           pc_rhs: branch,
                         } =>
                         Exp.case(
                           pattern,
                           Exp.sequence(
                             action
                             ->reducerLogEntry(`WithPayload)
                             ->logWithData("debugWithData", arg1->toData),
                             branch,
                           ),
                         )
                       | {
                           pc_lhs:
                             {
                               ppat_desc:
                                 Ppat_construct(
                                   {txt: Lident(action)},
                                   Some({
                                     ppat_desc:
                                       Ppat_tuple([
                                         {ppat_desc: Ppat_var({txt: arg1})},
                                         {ppat_desc: Ppat_var({txt: arg2})},
                                       ]),
                                   }),
                                 ),
                             } as pattern,
                           pc_rhs: branch,
                         } =>
                         Exp.case(
                           pattern,
                           Exp.sequence(
                             action
                             ->reducerLogEntry(`WithPayload)
                             ->logWithData2(
                                 "debugWithData2",
                                 arg1->toData,
                                 arg2->toData,
                               ),
                             branch,
                           ),
                         )
                       | {
                           pc_lhs:
                             {
                               ppat_desc:
                                 Ppat_construct(
                                   {txt: Lident(action)},
                                   Some({
                                     ppat_desc:
                                       Ppat_tuple([
                                         {ppat_desc: Ppat_var({txt: arg1})},
                                         {ppat_desc: Ppat_var({txt: arg2})},
                                         {ppat_desc: Ppat_var({txt: arg3})},
                                       ]),
                                   }),
                                 ),
                             } as pattern,
                           pc_rhs: branch,
                         } =>
                         Exp.case(
                           pattern,
                           Exp.sequence(
                             action
                             ->reducerLogEntry(`WithPayload)
                             ->logWithData3(
                                 "debugWithData3",
                                 arg1->toData,
                                 arg2->toData,
                                 arg3->toData,
                               ),
                             branch,
                           ),
                         )
                       | {
                           pc_lhs:
                             {
                               ppat_desc:
                                 Ppat_construct(
                                   {txt: Lident(action)},
                                   Some({
                                     ppat_desc:
                                       Ppat_tuple([
                                         {ppat_desc: Ppat_var({txt: arg1})},
                                         {ppat_desc: Ppat_var({txt: arg2})},
                                         {ppat_desc: Ppat_var({txt: arg3})},
                                         {ppat_desc: Ppat_var({txt: arg4})},
                                       ]),
                                   }),
                                 ),
                             } as pattern,
                           pc_rhs: branch,
                         } =>
                         Exp.case(
                           pattern,
                           Exp.sequence(
                             action
                             ->reducerLogEntry(`WithPayload)
                             ->logWithData4(
                                 "debugWithData4",
                                 arg1->toData,
                                 arg2->toData,
                                 arg3->toData,
                                 arg4->toData,
                               ),
                             branch,
                           ),
                         )
                       | {
                           pc_lhs:
                             {
                               ppat_desc:
                                 Ppat_construct(
                                   {txt: Lident(action)},
                                   Some({
                                     ppat_desc:
                                       Ppat_tuple([
                                         {ppat_desc: Ppat_var({txt: arg1})},
                                         {ppat_desc: Ppat_var({txt: arg2})},
                                         {ppat_desc: Ppat_var({txt: arg3})},
                                         {ppat_desc: Ppat_var({txt: arg4})},
                                         {ppat_desc: Ppat_var({txt: arg5})},
                                       ]),
                                   }),
                                 ),
                             } as pattern,
                           pc_rhs: branch,
                         } =>
                         Exp.case(
                           pattern,
                           Exp.sequence(
                             action
                             ->reducerLogEntry(`WithPayload)
                             ->logWithData5(
                                 "debugWithData5",
                                 arg1->toData,
                                 arg2->toData,
                                 arg3->toData,
                                 arg4->toData,
                                 arg5->toData,
                               ),
                             branch,
                           ),
                         )
                       | {
                           pc_lhs:
                             {
                               ppat_desc:
                                 Ppat_construct(
                                   {txt: Lident(action)},
                                   Some({
                                     ppat_desc:
                                       Ppat_tuple([
                                         {ppat_desc: Ppat_var({txt: arg1})},
                                         {ppat_desc: Ppat_var({txt: arg2})},
                                         {ppat_desc: Ppat_var({txt: arg3})},
                                         {ppat_desc: Ppat_var({txt: arg4})},
                                         {ppat_desc: Ppat_var({txt: arg5})},
                                         {ppat_desc: Ppat_var({txt: arg6})},
                                       ]),
                                   }),
                                 ),
                             } as pattern,
                           pc_rhs: branch,
                         } =>
                         Exp.case(
                           pattern,
                           Exp.sequence(
                             action
                             ->reducerLogEntry(`WithPayload)
                             ->logWithData6(
                                 "debugWithData6",
                                 arg1->toData,
                                 arg2->toData,
                                 arg3->toData,
                                 arg4->toData,
                                 arg5->toData,
                                 arg6->toData,
                               ),
                             branch,
                           ),
                         )
                       | {
                           pc_lhs:
                             {
                               ppat_desc:
                                 Ppat_construct(
                                   {txt: Lident(action)},
                                   Some({
                                     ppat_desc:
                                       Ppat_tuple([
                                         {ppat_desc: Ppat_var({txt: arg1})},
                                         {ppat_desc: Ppat_var({txt: arg2})},
                                         {ppat_desc: Ppat_var({txt: arg3})},
                                         {ppat_desc: Ppat_var({txt: arg4})},
                                         {ppat_desc: Ppat_var({txt: arg5})},
                                         {ppat_desc: Ppat_var({txt: arg6})},
                                         {ppat_desc: Ppat_var({txt: arg7})},
                                       ]),
                                   }),
                                 ),
                             } as pattern,
                           pc_rhs: branch,
                         } =>
                         Exp.case(
                           pattern,
                           Exp.sequence(
                             action
                             ->reducerLogEntry(`WithPayload)
                             ->logWithData7(
                                 "debugWithData7",
                                 arg1->toData,
                                 arg2->toData,
                                 arg3->toData,
                                 arg4->toData,
                                 arg5->toData,
                                 arg6->toData,
                                 arg7->toData,
                               ),
                             branch,
                           ),
                         )
                       | {
                           pc_lhs:
                             {
                               ppat_desc:
                                 Ppat_construct(
                                   {txt: Lident(action)},
                                   Some(_),
                                 ),
                             } as pattern,
                           pc_rhs: branch,
                         } =>
                         Exp.case(
                           pattern,
                           Exp.sequence(
                             action
                             ->reducerLogEntry(`WithNotLoggedPayload)
                             ->log("debug"),
                             branch,
                           ),
                         )
                       | _ => case
                       },
                     _,
                   ),
          ),
        ),
      )

    | _ => default_mapper.expr(mapper, expr)
    },
};

let () = Ast_mapper.register("bs-log", logMapper);