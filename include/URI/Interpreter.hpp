/**
 * @brief   The URI interpreter implementation plan.
 *
 * @author  spjuanjoc
 * @date    2021-06-09
 */

#ifndef UIN_INTERPRETER_H
#define UIN_INTERPRETER_H

/**
URI interpreter plan:

 1. Components
  scheme      mandatory
  path        mandatory
  authority
    host
    userinfo
    port
  query
  fragment

 2. Interface
    IResource
       Validate(host type: v4, v6, RN)
        - validate mandatory components
        - validate host sub component
        - then validate the rest
       GetComponent(component)

 3. Implementation
    Resource
      validate -> Dynamic Strategy
          Dynamic host parser
            Interface IParser
              IPv6Parser
              IPv4Parser
              RNParser
      get

 4. Usage
    lexer
    parser
      The dynamic strategy usage class

 5. resolver? interpreter?
    what to do with the parsed data
    auto parsed = parse("URI");
    parsed->validate(Host::IPv6);
    parsed->Get(Component::scheme)

 */

#endif /* UIN_INTERPRETER_H */
