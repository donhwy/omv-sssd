<?php
/**
 * @license   http://www.gnu.org/licenses/gpl.html GPL Version 3
 * @author    Volker Theile <volker.theile@openmediavault.org>
 * @copyright Copyright (c) 2009-2017 Volker Theile
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */
class OMVModuleNSSwitch extends \OMV\Engine\Module\ServiceAbstract
  implements \OMV\Engine\Notify\IListener {
    /**
     * Get the module name.
     */
    public function getName() {
        return "nsswitch";
    }

    /**
     * Generate the configuration.
     */
    public function applyConfig() {
        $cmd = new \OMV\System\Process("omv-mkconf", "nsswitch");
        $cmd->setRedirect2to1();
        $cmd->execute();
    }

    /**
     * Bind listeners.
     */
    function bindListeners(\OMV\Engine\Notify\Dispatcher $dispatcher) {
        $dispatcher->addListener(
          OMV_NOTIFY_MODIFY,
          "org.openmediavault.conf.service.sssd",
          [ $this, "setDirty" ]);
    }
}
