namespace simdjson {
namespace SIMDJSON_IMPLEMENTATION {
namespace ondemand {

/**
 * Iterates through JSON tokens (`{` `}` `[` `]` `,` `:` `"<string>"` `123` `true` `false` `null`)
 * detected by stage 1.
 *
 * @private This is not intended for external use.
 */
class token_iterator {
public:
  /**
   * Create a new invalid token_iterator.
   * 
   * Exists so you can declare a variable and later assign to it before use.
   */
  simdjson_really_inline token_iterator() noexcept = default;

  simdjson_really_inline token_iterator(token_iterator &&other) noexcept = default;
  simdjson_really_inline token_iterator &operator=(token_iterator &&other) noexcept = default;
  simdjson_really_inline token_iterator(const token_iterator &other) noexcept = delete;
  simdjson_really_inline token_iterator &operator=(const token_iterator &other) noexcept = delete;

  /**
   * Advance to the next token, return its text value.
   */
  simdjson_really_inline const uint8_t *next() noexcept;
  /**
   * Get the current token.
   */
  simdjson_really_inline const uint8_t *json() const noexcept;
  /**
   * Get the maximum length of the JSON text for the current token.
   */
  simdjson_really_inline uint32_t current_length() const noexcept;
  /**
   * Get the JSON text for a token besides the current one.
   *
   * This is not null-terminated; it is a view into the JSON.
   *
   * @param delta The relative position of the token to retrieve. -2 = previous token, 0 = next token, -1 = two tokens ahead.
   */
  simdjson_really_inline const uint8_t *peek(int32_t delta=0) const noexcept;
  /**
   * Get the maximum length of the JSON text for a given token.
   *
   * The length will include any whitespace at the end of the token.
   *
   * @param delta The relative position of the token to retrieve. -2 = previous token, 0 = next token, -1 = two tokens ahead.
   */
  simdjson_really_inline uint32_t peek_length(int32_t delta=0) const noexcept;

  // NOTE: we don't support a full C++ iterator interface, because we expect people to make
  // different calls to advance the iterator based on *their own* state.

  simdjson_really_inline bool operator==(const token_iterator &other) const noexcept;
  simdjson_really_inline bool operator!=(const token_iterator &other) const noexcept;
  simdjson_really_inline bool operator>(const token_iterator &other) const noexcept;
  simdjson_really_inline bool operator>=(const token_iterator &other) const noexcept;
  simdjson_really_inline bool operator<(const token_iterator &other) const noexcept;
  simdjson_really_inline bool operator<=(const token_iterator &other) const noexcept;

protected:
  simdjson_really_inline token_iterator(const uint8_t *buf, uint32_t *next_index) noexcept;

  /**
   * Get the index of the JSON text for a given token (relative).
   *
   * This is not null-terminated; it is a view into the JSON.
   *
   * @param delta The relative position of the token to retrieve. -2 = previous token, 0 = next token, -1 = two tokens ahead.
   */
  simdjson_really_inline uint32_t peek_index(int32_t delta=0) const noexcept;

  const uint8_t *buf{};
  const uint32_t *next_index{};
  const uint8_t *current_json{};
};

} // namespace ondemand
} // namespace SIMDJSON_IMPLEMENTATION
} // namespace simdjson

namespace simdjson {

template<>
struct simdjson_result<SIMDJSON_IMPLEMENTATION::ondemand::token_iterator> : public SIMDJSON_IMPLEMENTATION::implementation_simdjson_result_base<SIMDJSON_IMPLEMENTATION::ondemand::token_iterator> {
public:
  simdjson_really_inline simdjson_result(SIMDJSON_IMPLEMENTATION::ondemand::token_iterator &&value) noexcept; ///< @private
  simdjson_really_inline simdjson_result(error_code error) noexcept; ///< @private

  simdjson_really_inline simdjson_result() noexcept = default;
  simdjson_really_inline simdjson_result(simdjson_result<SIMDJSON_IMPLEMENTATION::ondemand::token_iterator> &&a) noexcept = default;
  simdjson_really_inline ~simdjson_result() noexcept = default; ///< @private
};

} // namespace simdjson
