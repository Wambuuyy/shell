/**
 *  * is_chain - Tests if the current character in the buffer is a chain delimiter
 *   * @input: Input struct
 *    * @buf: Character buffer
 *     * @p: Address of the current position in buf
 *      *
 *       * Return: 1 if a chain delimiter, 0 otherwise
 *        */
int is_chain(Input *input, char *buf, size_t *p)
{
	    size_t j = *p;

	        if (buf[j] == '|' && buf[j + 1] == '|') {
			        buf[j] = 0;
				        j++;
					        input->cmd_buf_type = CMD_OR;
						    } else if (buf[j] == '&' && buf[j + 1] == '&') {
							            buf[j] = 0;
								            j++;
									            input->cmd_buf_type = CMD_AND;
										        } else if (buf[j] == ';') {
												        buf[j] = 0;
													        input->cmd_buf_type = CMD_CHAIN;
														    } else {
															            return 0;
																        }

		    *p = j;
		        return 1;
}

/**
 *  * check_chain - Checks if we should continue chaining based on the last status
 *   * @input: Input struct
 *    * @buf: Character buffer
 *     * @p: Address of the current position in buf
 *      * @i: Starting position in buf
 *       * @len: Length of buf
 *        *
 *         * Return: Void
 *          */
void check_chain(Input *input, char *buf, size_t *p, size_t i, size_t len)
{
	    size_t j = *p;

	        if (input->cmd_buf_type == CMD_AND) {
			        if (input->status) {
					            buf[i] = 0;
						                j = len;
								        }
				    }

		    if (input->cmd_buf_type == CMD_OR) {
			            if (!input->status) {
					                buf[i] = 0;
							            j = len;
								            }
				        }

		        *p = j;
}

