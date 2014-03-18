Conventions Used in This Documentation                      {#conventions}
======================================

# Exception Guarantees                                      {#exceptguarantee}
Every C++ function can be said to have one of the following *exception
guarantees*, that is, guarantees about the behavior and state of the program
after an exception is thrown.

  * **None**: If an exception is thrown from the function, the program is left
    in an undefined state.
  * **Weak**: If an exception is thrown from the function, no resources
    allocated within the function will be leaked.  The program state is left in
    an undefined but valid state.
  * **Strong**: If an exception is thrown from the function, the state of the
    program is left as it was before the function call.
  * **Noexcept**: No exception will be thrown from the function.  The operation
    performed by the function will always succeed.

In the Humm and Strumm Engine, no functions have an exception guarantee of
None.  That is, all functions in the Humm and Strumm Engine are exception-safe.

The exception guarantees of the functions in the Humm and Strumm Engine are
documented in the following way:

@exceptguarantee The exception guarantee as defined above, as well as any
additional guarantees about the behavior of the function when an exception is
thrown.  The exception guarantee does not specify whether any exceptions will be
thrown or what exceptions may be thrown under specific conditions.

The exception guarantee of some function template instantiations may depend on
the template arguments used to instantiate the template.  Similarly, the
exception guarantee of some higher-order functions may depend on the `Callable`
arguments passed into them.  The exception guarantee specification for these
functions or function templates will explain how the exception guarantee for the
template arguments or `Callable` arguments affect the exception guarantee for
the function or function template instantiations.  Alternatively, the function
may specify a precondition or the function template may specify requirements on
the template arguments to ensure that the function or function template will
necessarily have a certain exception guarantee.
