(
  (nil .      ((require-final-newline t))
  (text .     ((tab-width 8)
               (fill column 79)))
  (c++-mode . ((c-set-style "GNU")
               (indent-tabs-mode nil)
               (auto-fill-mode)))
)

; statement

; c-cleanup-list:
;   empty-defun-braces
;   defun-close-semi
;   list-close-coma
;   scope-operator
;   space-before-funcall

; c-hanging-colons-alist
;   case-label after
;   label after
;   access-label after
;   member-init-intro before
;   inher-intro

; c-hanging-braces-alist
;   brace-list-open
