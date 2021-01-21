#include <eosio/eosio.hpp>

using namespace eosio;

class [[eosio::contract("pembukuan")]] pembukuan : public eosio::contract {
  public:
  
  pembukuan(name receiver, name code, datastream<const char*> ds):contract(receiver, code, ds) {}

  [[eosio::action]]
  void pemasukan( name user, uint64_t pemasukan) {
  require_auth( user );
  catatan_pemasukan pemasukan_table(get_self(), get_first_receiver().value);
  auto iterator = pemasukan_table.find(user.value);
  if( iterator == pemasukan_table.end() )
  {
      pemasukan_table.emplace(user, [&] ( auto& row ) {
      row.user = user;
      row.pemasukan = pemasukan;

    });

  } else {
      pemasukan_table.modify(iterator, user, [&] ( auto& row ) {
      row.user = user;
      row.pemasukan = pemasukan;
    });
  }
}

  [[eosio::action]]
  void pengeluaran( name user, uint64_t pengeluaran){
  require_auth( user );
  catatan_pengeluaran pengeluaran_table(get_self(), get_first_receiver().value);
  auto iterator = pengeluaran_table.find(user.value);
  if( iterator == pengeluaran_table.end() )
  {
    pengeluaran_table.emplace(user, [&] ( auto& row ) {
    row.user = user;
    row.pengeluaran = pengeluaran;

    });
    
  } else {
    pengeluaran_table.modify(iterator, user, [&] ( auto& row ) {
    row.user = user;
    row.pengeluaran = pengeluaran;
    });
  }
}

  private:
  struct [[eosio::table]] pemasukan_row {
  name user;
  uint64_t pemasukan;

  auto primary_key() const { return user.value; }
  };

  typedef eosio::multi_index<"pemasukan"_n, pemasukan_row> catatan_pemasukan;

  struct [[eosio::table]] pengeluaran_row {
  name user;
  uint64_t pengeluaran;
 

  auto primary_key() const { return user.value; }
  };

  typedef eosio::multi_index<"pengeluaran"_n, pengeluaran_row> catatan_pengeluaran;

// Yuda Adi Pratama
};