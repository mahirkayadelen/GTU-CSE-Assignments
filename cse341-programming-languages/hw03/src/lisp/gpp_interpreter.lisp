;; gppinterpreter function starts interpreter
(defun gppinterpreter (&optional (filename nil is_filename_supplied))
  (if is_filename_supplied
    (start-interpreter-from-file filename)
    (start-interpreter-from-shell)
  )
)
;; read line by line from file and evaluate
(defun start-interpreter-from-file (filename)
  (open-file-to-write "parsed_lisp.txt")
  (print "File has created.")
  (with-open-file (stream filename :direction :input)
    (loop for line1 = (read-line stream nil)
      while line1 do (if (> (length line1) 0)
                         (if (not (is-comment line1))
                           (progn (setf currentLine line1)
                            (tokenize-one-line line1))))
      )
  )
)
;;read from terminal until empty string and evaluate given text.
(defun start-interpreter-from-shell ()
 (princ "Welcome to G++ shell made by Mahir with Lisp, to exit enter empty string")
 (open-file-to-write "parsed_lisp.txt")
 (format t "~%") (princ "> ")
  (let ((line ""))
    (loop for newLine = (read-line)
      while (> (length newLine) 0) do (if (not (is-comment newLine))
                                      (progn (setf currentLine newLine)
                                             (tokenize-one-line newLine)))
    )
   (print "File has created.")
  )
)
;;split line from spaces and evaluate splitted tokens one by one.
(defun tokenize-one-line (line)
  ;; Trim leading and trailing whitespace from the line
  (setf line (string-trim '(#\Space #\Tab #\Newline) line))

  ;; Split the line into tokens
  (let ((tokens (str-split line)))
    ;; Check if there's only one token and if it's a VALUEF
    (if (and (= (length tokens) 1) (is-valuef (first tokens)))
        (write-lexical-result-to-file (first tokens) nil) ; Write VALUEF as the result
        ;; If not a single VALUEF, process each token
        (loop for token in tokens do (start-DFA-part1 token)))))


              
;;Apply DFA analysis steps for 1 character tokens
(defun start-DFA-part1 (token)
  (cond
    ;; Handle single character tokens (operators, identifiers, etc.)
    ((= 1 (length token))
     (let ((chr (char token 0)))
       (cond ((is-operator chr) t)
             ((alpha-char-p chr) (write-lexical-result-to-file "IDENTIFIER" nil))
             ((char= #\Newline chr) t)
             (t (write-lexical-result-to-file chr t)))))
    ;; If the token is not a single character, pass it to part2 for further processing
    (t (start-DFA-part2 token)))
)

;;Apply DFA analysis steps for long tokens
(defun start-DFA-part2 (token)
  (cond ((is-keyword token) t)
    ((is-comment token) t)
    ((is-valuef2 token) t) ;; for 
    ((is-identifier token) t)
    ((check-tabs-and-paranthesis token) t)
    (t (write-lexical-result-to-file token t)))
)
;;determine paranthesis
(defun check-paranthesis-and-quotes (token)
  (if (or (char= (char token 0) #\() (char= (char token 0) #\“)
          (char= (char token (- (length token) 1)) #\)) (char= (char token (- (length token) 1)) #\”))
    (progn (print-begin-paranthesis-and-quotes token) t) nil)
)
;;determine tabs
(defun check-tabs-and-paranthesis (token)
  (if (char= (char token 0) #\Tab)
    (progn (remove-tabs token) t) (check-paranthesis-and-quotes token))
)
;;remove tabs to make correct analysis
(defun remove-tabs (token)
  (let ((counter 0))
    (loop for chr across token
      while (char= chr #\Tab) do (setf token (remove #\Tab token :count 1))
    )
    (start-DFA-part1 token)
  )
)
;;check for operators
(defun is-operator (chr)
  (cond ((char= chr #\+) (resolve-given-command "OP_PLUS"))
    ((char= chr #\-) (resolve-given-command "OP_MINUS"))
    ((char= chr #\/) (resolve-given-command "OP_DIV"))
    ((char= chr #\*) (resolve-given-command "OP_MULT"))
    ((char= chr #\() (write-lexical-result-to-file "OP_OP" nil))
    ((char= chr #\)) (write-lexical-result-to-file "OP_CP" nil))
    ((char= chr #\,) (write-lexical-result-to-file "OP_COMMA" nil))
    (t nil))

)

;;check for comment
(defun is-comment (token)
(if (> (length token) 1)
  (if (search ";;" token :end2 2) (write-lexical-result-to-file "COMMENT" nil) nil) nil)

)






;;check for keywords
(defun is-keyword (token)
  (cond ((string= token "and") (write-lexical-result-to-file "KW_AND" 1))
    ((string= token "or") (write-lexical-result-to-file "KW_OR" 1))
    ((string= token "not") (write-lexical-result-to-file "KW_NOT" 1))
    ((string= token "equal") (write-lexical-result-to-file "KW_EQUAL" 1))
    ((string= token "less") (write-lexical-result-to-file "KW_LESS" 1))
    ((string= token "nil") (write-lexical-result-to-file "KW_NIL" 1))
    ((string= token "list") (write-lexical-result-to-file "KW_LIST" 1))
    ((string= token "append") (write-lexical-result-to-file "KW_APPEND" nil))
    ((string= token "concat") (write-lexical-result-to-file "KW_CONCAT" nil))
    ((string= token "set") (write-lexical-result-to-file "KW_SET" 1))
    ((string= token "def") (write-lexical-result-to-file "KW_DEF" nil))
    ((string= token "for") (write-lexical-result-to-file "KW_FOR" nil))
    ((string= token "if") (write-lexical-result-to-file "KW_IF" nil))
    ((string= token "exit") (resolve-exit))
    ((string= token "load") (write-lexical-result-to-file "KW_LOAD" nil))
    ((string= token "display") (write-lexical-result-to-file "KW_DISPLAY" 1))
    ((string= token "true") (write-lexical-result-to-file "KW_TRUE" nil))
    ((string= token "false") (write-lexical-result-to-file "KW_FALSE" nil))
    (t nil))
)

;;check for values
;; Check for fractional values
(defun is-valuef (token)
  (let ((value-parts (str-split token :delimiterp #'(lambda (c) (char= c #\b)))))
    (if (= (length value-parts) 2)
        (if (and (every #'is-digit (car value-parts))
                 (every #'is-digit (cadr value-parts)))
            (progn
              ;; Write formatted fractional value to file
              (write-lexical-result-to-file2 (format nil "~a~a~a" 
                                                     (car value-parts) #\b (cadr value-parts)))
              t) ; Return t to indicate successful handling of VALUEF
            nil) ; Return nil if not a valid VALUEF
        nil))) ; Return nil if not correctly formatted as a fraction




;;check for values
;; Check for fractional values
(defun is-valuef2 (token)
  (let ((value-parts (str-split token :delimiterp #'(lambda (c) (char= c #\b)))))
    (if (= (length value-parts) 2)
        (if (and (every #'is-digit (car value-parts))
                 (every #'is-digit (cadr value-parts)))
            (write-lexical-result-to-file "VALUEF" nil) nil)))
)

;;check for digits
(defun is-digit (chr)
(cond ((char= chr #\0) t)
  ((char= chr #\1) t)
  ((char= chr #\2) t)
  ((char= chr #\3) t)
  ((char= chr #\4) t)
  ((char= chr #\5) t)
  ((char= chr #\6) t)
  ((char= chr #\7) t)
  ((char= chr #\8) t)
  ((char= chr #\9) t)
  (t nil))
)
;;check for identifiers
(defun is-identifier (token)
  (if (is-digit (char token 0)) 
      nil
      (if (every #'alphanumericp token)
          (progn
            ;; Write "0b1" to the file if it's an identifier
            (write-lexical-result-to-file2 "0b1")
            t)  ; Return true to indicate it's an identifier
          nil)))  ; Return nil if it's not an identifier

;;print and remove paranthesis to make correct analysis
(defun print-begin-paranthesis-and-quotes (token)
  (let ()
    (loop for chr across token
      while (or (char= chr #\() (char= chr #\“)) do (progn (is-operator chr)
                                                           (setf token (remove chr token :count 1)))
    )
    (check-end-paranthesis-and-quotes token (get-end-paranthesis-and-quotes token))
  )
)
;;get last paranthesis as list
(defun get-end-paranthesis-and-quotes (token)
  (setf token (reverse token))
  (loop for chr across token
    while (or (char= chr #\)) (char= chr #\”)) collect chr
  )
)
;;print last paranthesis and apply DFA steps one more time.
(defun check-end-paranthesis-and-quotes (token mylist)
 (last-control token (list-length mylist))
 (setf mylist (reverse mylist))
 (if (or (/= (list-length mylist) 1) (/= (length token) 1))
 (loop for parenth in mylist
   while parenth do (is-operator parenth)
 ))
)
;;apply DFA steps one more time after paranthesis were removed.
(defun last-control (token size)
  (let ((end (- (length token) size)))
       (if (= (length token) 1) (start-DFA-part1 token)
         (start-DFA-part1 (subseq token 0 end)))
  )
)
;;open file in supersede mode to create.
(defun open-file-to-write (filename)
  (with-open-file (stream filename  :direction :output
                                    :if-exists :supersede
                                    :if-does-not-exist :create))
)
;;open file in append mode to write.
(defun write-lexical-result-to-file (lexical_result is_error)
   (with-open-file (stream "parsed_lisp.txt" :direction :output
                                                :if-exists :append
                                                :if-does-not-exist :create)
         (if is_error
           (progn (write-sequence (format nil "Syntax Error! ~a cannot evaluated.~%" (string lexical_result)) stream)
                  )
           1))
 ;;(if is_error (exit))
);;open file in append mode to write.
(defun write-lexical-result-to-file2 (lexical_result)
   (with-open-file (stream "parsed_lisp.txt" :direction :output
                                                :if-exists :append
                                                :if-does-not-exist :create)

    (write-sequence (format nil "SYNTAX OK.~%Result: ~a~%" lexical_result) stream)
   )
)
(defun write-lexical-result-to-file3 ()
   (with-open-file (stream "parsed_lisp.txt" :direction :output
                                                :if-exists :append
                                                :if-does-not-exist :create)

    (write-sequence (format nil "Syntax Error!~%") stream)
   )
)

(defun resolve-given-command (command)
  (cond ((string= command "OP_PLUS") (resolve-plus))
    ((string= command "OP_MINUS") (resolve-minus))
    ((string= command "OP_DIV") (resolve-div))
    ((string= command "OP_MULT") (resolve-mult))
    (t nil))
)
(defun resolve-plus ()
  (let ((params (str-split (str-remove "(" (str-remove ")" (str-remove "+" currentLine)))))
        (result 0) (result-denom 1))
    ;; Check if the number of parameters is more than 2
    (if (> (length params) 2)
        (write-lexical-result-to-file3)  ; Handle syntax error for more than 2 operands
        (progn
          (loop for element in params
            do (let ((frac-parts (str-split element :delimiterp #'(lambda (c) (char= c #\b)))))
                 (if (= (length frac-parts) 2)
                     (let ((num (parse-integer (car frac-parts)))
                           (denom (parse-integer (cadr frac-parts))))
                       (if (/= result-denom denom)
                           (setf result (+ (* result denom) (* num result-denom))
                                 result-denom (* result-denom denom))
                           (setf result (+ result num))))
                     (if (typep (read-from-string element) 'integer)
                         (setf result (+ result (parse-integer element)))
                         (write-lexical-result-to-file3)))))
          (let ((gcd (gcd result result-denom)))
            (setf result (/ result gcd))
            (setf result-denom (/ result-denom gcd)))
              (write-lexical-result-to-file2 (format nil "~a~a~a" result #\b result-denom)))))
)

(defun resolve-minus ()
  (let ((params (str-split (str-remove "(" (str-remove ")" (str-remove "-" currentLine)))))
        (result nil) (result-denom nil) (first-element t))
    ;; Check if the number of parameters is more than 2
    (if (> (length params) 2)
        (write-lexical-result-to-file3)  ; Handle syntax error for more than 2 operands
        (progn
          (loop for element in params
            do (let ((frac-parts (str-split element :delimiterp #'(lambda (c) (char= c #\b)))))
                 (if (= (length frac-parts) 2)
                     (let ((num (parse-integer (car frac-parts)))
                           (denom (parse-integer (cadr frac-parts))))
                       (if first-element
                           (progn
                             (setf result num)
                             (setf result-denom denom)
                             (setf first-element nil))
                           (progn
                             (setf result (- (* result denom) (* num result-denom)))
                             (setf result-denom (* result-denom denom)))))
                     (if (typep (read-from-string element) 'integer)
                         (if first-element
                             (progn
                               (setf result (parse-integer element))
                               (setf first-element nil))
                             (progn
                               (setf result (- result (parse-integer element)))
                               (setf result-denom (if result-denom (* result-denom 1) 1))))))))
          (let ((gcd (gcd result result-denom)))
            (setf result (/ result gcd))
            (setf result-denom (/ result-denom gcd)))
              (write-lexical-result-to-file2 (format nil "~a~a~a" result #\b result-denom)))))
)


(defun resolve-div ()
  (let ((params (str-split (str-remove "(" (str-remove ")" (str-remove "/" currentLine)))))
        (result nil) (result-denom nil) (first-element t))
    ;; Check if the number of parameters is more than 2
    (if (> (length params) 2)
        (write-lexical-result-to-file3)  ; Handle syntax error for more than 2 operands
        (progn
          (loop for element in params
            do (let ((frac-parts (str-split element :delimiterp #'(lambda (c) (char= c #\b)))))
                 (if (= (length frac-parts) 2)
                     (let ((num (parse-integer (car frac-parts)))
                           (denom (parse-integer (cadr frac-parts))))
                       (if first-element
                           (progn
                             (setf result num)
                             (setf result-denom denom)
                             (setf first-element nil))
                           (progn
                             (setf result (* result denom))
                             (setf result-denom (* result-denom num)))))
                     (if (typep (read-from-string element) 'integer)
                         (if first-element
                             (progn
                               (setf result (parse-integer element))
                               (setf first-element nil))
                             (progn
                               (setf result (* result (parse-integer element)))
                               (setf result-denom (if result-denom (* result-denom 1) 1))))))))
          (let ((gcd (gcd result result-denom)))
            (setf result (/ result gcd))
            (setf result-denom (/ result-denom gcd)))
              (write-lexical-result-to-file2 (format nil "~a~a~a" result #\b result-denom)))))
)


(defun resolve-mult ()
  (let ((params (str-split (str-remove "(" (str-remove ")" (str-remove "*" currentLine)))))
        (result 1) (result-denom 1))
    ;; Check if the number of parameters is more than 2
    (if (> (length params) 2)
        (write-lexical-result-to-file3)  ; Handle syntax error for more than 2 operands
        (progn
          (loop for element in params
            do (let ((frac-parts (str-split element :delimiterp #'(lambda (c) (char= c #\b)))))
                 (if (= (length frac-parts) 2)
                     (let ((num (parse-integer (car frac-parts)))
                           (denom (parse-integer (cadr frac-parts))))
                       (setf result (* result num))
                       (setf result-denom (* result-denom denom)))
                     (if (typep (read-from-string element) 'integer)
                         (setf result (* result (parse-integer element)))
                         (write-lexical-result-to-file3)))))
          (let ((gcd (gcd result result-denom)))
            (setf result (/ result gcd))
            (setf result-denom (/ result-denom gcd)))
              (write-lexical-result-to-file2 (format nil "~a~a~a" result #\b result-denom)))))
)



(defun resolve-exit()
   (let ((params (str-split (str-remove "(" (str-remove ")" currentLine)))) (broken nil))
     (if (/= (length params) 1) (write-lexical-result-to-file3))
     (if (not (string= (nth 0 params) "exit")) (write-lexical-result-to-file3))
     (if broken
       (write-lexical-result-to-file3)
       (progn (write-lexical-result-to-file2 "exiting...")
              (exit))
    )
  )
)

;;--------------------------HELPER FUNCS -------------------------------
;; this function split a string from delimeter(space or comma)
(defun str-split (string &key (delimiterp #'delimiterp))
  (loop :for beg = (position-if-not delimiterp string)
    :then (position-if-not delimiterp string :start (1+ end))
    :for end = (and beg (position-if delimiterp string :start beg))
    :when beg :collect (subseq string beg end)
    :while end)
)
;; this function remove a substring from string
(defun str-remove (rem-string full-string &key from-end (test #'eql)
                      test-not (start1 0) end1 (start2 0) end2 key)
  "returns full-string with rem-string removed"
  (let ((subst-point (search rem-string full-string
                             :from-end from-end
                             :test test :test-not test-not
                             :start1 start1 :end1 end1
                             :start2 start2 :end2 end2 :key key)))
    (if subst-point
        (concatenate 'string
                     (subseq full-string 0 subst-point)
                     (subseq full-string (+ subst-point (length rem-string))))
        full-string))
)
(defun delimiterp (c) (or (char= c #\Space) (char= c #\,)))
;;---------------------------------------------------------------------------

(setq currentLine "")
;;check given command line arguments
(defun start-tokenization ()
  (if *args*
    (gppinterpreter (first *args*))
    (gppinterpreter))
)
(start-tokenization)