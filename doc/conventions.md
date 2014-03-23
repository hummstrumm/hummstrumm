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

# Invariants                                                {#invariants}
*Invariants* are properties about a type abstraction that can be assumed to be
true for any valid objects of that type.  An object whose invariants are
satisfied is said to be a *valid* object.  Most functions require that their
arguments or `*this` objects be valid objects.  See the section @ref movesem for
a case where this may not be true.

Within this documentation, we draw a distinction between two different types of
invariants: *private* invariants, which are invariants on the part of the
implementation that are encapsulated away from the user, and *public*
invariants, which are invariants on the object state that form a fundamental
part of the abstraction.  A user of a type may rely on its public invariants,
but cannot rely (and should not be exposed to) its private invariants.

Within the Humm and Strumm Engine, we follow the convention that each type
declared with the keyword `class` preserves some invariant or some set of
invariants on its data members, and each type declared with the keyword `struct`
does not preserve any invariant.  These invariants are documented using
invariant blocks:

@invariant This block details the non-implementation specific invariants on the
state of an object of the type.  Invariants that are preserved that the user
cannot see will not be documented in this block.

# Move Semantics                                            {#movesem}
In the subset of C++ that does not include move semantics, the Humm and Strumm
Engine is designed so that, as long as function preconditions are satisfied
(see @ref prepostcond for more details), no object can reach an invalid state.
With move semantics, though, this is not possible.  After moving from an object,
it may be left in an invalid state, so most functions may not be applied to it.
In general, the only operations that may be applied to an invalid object are the
assignment operator and the destructor.  Because all objects must be destructed,
a destructor must be able to cope with an invalid object.  With an assignment
operator call, an invalid object can be turned into a valid object by copying or
moving from an existing valid object.

# Preconditions and Postconditions                          {#prepostcond}
Every function in the Humm and Strumm Engine has a set of *preconditions* and
*postconditions* which formally define the context in which the function can be
called and the effect on that context which the function has.  Preconditions are
requirements that the caller must guarantee to be true at the time the function
is called.  When these preconditions are broken, the behavior of the function is
undefined.  Postconditions, sometimes known as *effects*, are the guarantees
that the function makes that will be true at the time the function returns, as
long as the preconditions are true.

Functions may have either a *narrow* or *wide contract*.  A function with a
narrow contract has preconditions: certain combinations of input or state may
result in undefined behavior.  A function with a wide contract has no
preconditions, and all combinations of input or state have a defined effect.  As
an example, a function `float div(float a, float b)` has a wide contract if it
accepts any values `a` and `b`, and is guaranteed to, for instance, throw an
exception when `b == 0.f` or when `a` or `b` are NaN or infinity,  and return
the IEEE floating point division for all other values of `a` and `b`.  The `div`
function has a narrow contract if it accepts only `a` and `b` such that `b
!= 0.f` and `a` and `b` are not NaN or infinity, and returns the IEEE floating
point division of `a` and `b`.  Because the effects of `div` are undefined when
`b == 0.f`, for example, the implementation may throw an exception, it may
return a bogus value, or it may crash the application.

The preconditions and postconditions are specified more formally than the
description of the function, but contain similar information.  The description
is better to understand the purpose of the function.  The following blocks are
included in most functions:

@pre This block describes the preconditions of a function.  If there are no
preconditions, this block is not included.

@post This block describes the postconditions of a function.  If the
postconditions are not able to be specified formally (for example, debug message
formats that may change), this block is not included.

All functions have an implicit postcondition that their `*this` object, if any,
remains valid.
