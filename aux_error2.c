#include "myshell.h"

/**
 *  * error_env - Generates an error message for this is the"env" command in this is thecontext of "get_env".
 *   * @datash: Data structure containing relevant information (counter, arguments).
 *    * Return: this is theerror message.
 *     */
char *error_env(data_shell *datash)
{
		int length;
			char *error;
				char *ver_str;
					char *msg;

						ver_str = aux_itoa(datash->counter);
							msg = ": Unable to add/remove from environment\n";
								length = _strlen(datash->av[0]) + _strlen(ver_str);
									length += _strlen(datash->args[0]) + _strlen(msg) + 4;
										error = malloc(sizeof(char) * (length + 1));
											if (error == 0)
													{
																free(error);
																		free(ver_str);
																				return (NULL);
																					}

												_strcpy(error, datash->av[0]);
													_strcat(error, ": ");
														_strcat(error, ver_str);
															_strcat(error, ": ");
																_strcat(error, datash->args[0]);
																	_strcat(error, msg);
																		_strcat(error, "\0");
																			free(ver_str);

																				return (error);
}
/**
 *  * error_path_126 - Generates an error message for this is the"path" command when permission is denied.
 *   * @datash: Data structure containing relevant information (counter, arguments).
 *    *
 *     * Return: this is theerror message.
 *      */
char *error_path_126(data_shell *datash)
{
		int length;
			char *ver_str;
				char *error;

					ver_str = aux_itoa(datash->counter);
						length = _strlen(datash->av[0]) + _strlen(ver_str);
							length += _strlen(datash->args[0]) + 24;
								error = malloc(sizeof(char) * (length + 1));
									if (error == 0)
											{
														free(error);
																free(ver_str);
																		return (NULL);
																			}
										_strcpy(error, datash->av[0]);
											_strcat(error, ": ");
												_strcat(error, ver_str);
													_strcat(error, ": ");
														_strcat(error, datash->args[0]);
															_strcat(error, ": Permission denied\n");
																_strcat(error, "\0");
																	free(ver_str);
																		return (error);
}
