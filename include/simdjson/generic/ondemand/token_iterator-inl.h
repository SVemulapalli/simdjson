namespace simdjson {
namespace SIMDJSON_IMPLEMENTATION {
namespace ondemand {

simdjson_really_inline token_iterator::token_iterator(const uint8_t *_buf, uint32_t *_next_index) noexcept
  : buf{_buf}, next_index{_next_index}
{
}

simdjson_really_inline const uint8_t *token_iterator::next() noexcept {
  return current_json = &buf[*(next_index++)];
}
simdjson_really_inline const uint8_t *token_iterator::json() const noexcept {
  return current_json;
}
simdjson_really_inline uint32_t token_iterator::current_length() const noexcept {
  return static_cast<uint32_t>(&buf[*next_index] - current_json);
}

simdjson_really_inline const uint8_t *token_iterator::peek(int32_t delta) const noexcept {
  return &buf[*(next_index+delta)];
}
simdjson_really_inline uint32_t token_iterator::peek_length(int32_t delta) const noexcept {
  return peek_index(delta+1) - peek_index(delta);
}
simdjson_really_inline uint32_t token_iterator::peek_index(int32_t delta) const noexcept {
  return *(next_index+delta);
}

simdjson_really_inline bool token_iterator::operator==(const token_iterator &other) const noexcept {
  return next_index == other.next_index;
}
simdjson_really_inline bool token_iterator::operator!=(const token_iterator &other) const noexcept {
  return next_index != other.next_index;
}
simdjson_really_inline bool token_iterator::operator>(const token_iterator &other) const noexcept {
  return next_index > other.next_index;
}
simdjson_really_inline bool token_iterator::operator>=(const token_iterator &other) const noexcept {
  return next_index >= other.next_index;
}
simdjson_really_inline bool token_iterator::operator<(const token_iterator &other) const noexcept {
  return next_index < other.next_index;
}
simdjson_really_inline bool token_iterator::operator<=(const token_iterator &other) const noexcept {
  return next_index <= other.next_index;
}

} // namespace ondemand
} // namespace SIMDJSON_IMPLEMENTATION
} // namespace simdjson

namespace simdjson {

simdjson_really_inline simdjson_result<SIMDJSON_IMPLEMENTATION::ondemand::token_iterator>::simdjson_result(SIMDJSON_IMPLEMENTATION::ondemand::token_iterator &&value) noexcept
    : implementation_simdjson_result_base<SIMDJSON_IMPLEMENTATION::ondemand::token_iterator>(std::forward<SIMDJSON_IMPLEMENTATION::ondemand::token_iterator>(value)) {}
simdjson_really_inline simdjson_result<SIMDJSON_IMPLEMENTATION::ondemand::token_iterator>::simdjson_result(error_code error) noexcept
    : implementation_simdjson_result_base<SIMDJSON_IMPLEMENTATION::ondemand::token_iterator>(error) {}

} // namespace simdjson
